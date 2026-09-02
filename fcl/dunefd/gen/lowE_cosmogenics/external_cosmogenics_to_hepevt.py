#!/usr/bin/env python3
"""
external_cosmogenics_to_hepevt.py
----------------------------------
Write a LArSoft HEPEVT file of external cosmogenics for TextFileGen.

"External cosmogenics" are particles produced by cosmic-ray interactions in the
surrounding rock that subsequently enter the DUNE FD HD detector. Their species,
energy and angular distributions come from a standalone G4 campaign, reduced to
external_cosmogenics_table.dat by make_external_cosmogenics_table.py.

The table bins energy and direction SEPARATELY, so any correlation between the
two is not reproduced -- see README.md, which also says how to obtain the full
unreduced CSV if you need it.

Entry face: central APA plane of the 1x2x6 (x = 0 cm).
Positions are sampled uniformly over the APA face: y in [-305, 305], z in [0, 1394] cm.

Coordinate convention:
  Table uses x=beam, y=vertical, z=drift, and cos(theta) is measured about z.
  LArSoft uses x=drift, y=vertical, z=beam. The x and z components are swapped.

Direction handling:
  After the coordinate swap the LArSoft-x (drift) component is flipped with 50%
  probability so that both drift volumes on either side of the central APA are
  equally populated. dirY and dirZ (beam) are never flipped.

Exposure scaling:
  The table records how many particles each species contributed at the source
  normalisation. Each species emits Poisson(n_species * scale) particles, with
  scale = target_ktondays / norm_ktondays. Every particle gets an independent
  energy, direction, position and drift-sign draw.

Usage:
  python external_cosmogenics_to_hepevt.py external_cosmogenics_table.dat output.hepevt \
      --norm-ktondays 5980 --target-ktondays 36500 [--seed 42]
"""

import sys
import bisect
import math
import random
import argparse

# APA plane entry position
X_ENTRY = 0.0   # cm  (central APA plane)

# APA face bounds (from dune_cosmogenics_model_hd_1x2x6.fcl)
Y_LO, Y_HI = -305.0,  305.0   # cm
Z_LO, Z_HI =    0.0, 1394.0   # cm

# PDG masses in GeV
PDG_MASS = {
    22:    0.0,          # gamma
    12:    0.0,          # nu_e
    14:    0.0,          # nu_mu
    16:    0.0,          # nu_tau
    11:    0.000511,     # e-
   -11:    0.000511,     # e+
    13:    0.105658,     # mu-
   -13:    0.105658,     # mu+
    211:   0.139570,     # pi+
   -211:   0.139570,     # pi-
    111:   0.134977,     # pi0
    130:   0.497611,     # K0_L
    321:   0.493677,     # K+
   -321:   0.493677,     # K-
    2112:  0.939565,     # neutron
   -2112:  0.939565,     # antineutron
    2212:  0.938272,     # proton
   -2212:  0.938272,     # antiproton
    1000020040: 3.727379,   # alpha (He-4)
    1000010020: 1.875613,   # deuteron
    1000010030: 2.808921,   # triton
}

_LABEL = {
    22: 'gamma', 12: 'nu_e', 14: 'nu_mu', 16: 'nu_tau',
    11: 'e-', -11: 'e+', 13: 'mu-', -13: 'mu+',
    211: 'pi+', -211: 'pi-', 111: 'pi0',
    130: 'K0_L', 321: 'K+', -321: 'K-',
    2112: 'neutron', -2112: 'antineutron',
    2212: 'proton', -2212: 'antiproton',
    1000020040: 'alpha',
    1000010020: 'deuteron',
    1000010030: 'triton',
}

_warned_pdg = set()


def get_mass(pdg):
    """Return mass in GeV; warn once for unknown PDG codes and assume massless."""
    if pdg in PDG_MASS:
        return PDG_MASS[pdg]
    if pdg not in _warned_pdg:
        print(f"WARNING: PDG {pdg} not in mass table, assuming massless. "
              f"Add it to PDG_MASS if this is wrong.", file=sys.stderr)
        _warned_pdg.add(pdg)
    return 0.0


def poisson(mu):
    """Draw one sample from Poisson(mu)."""
    if mu == 0:
        return 0
    if mu < 30:
        # Knuth algorithm (exact)
        L = math.exp(-mu)
        k, p = 0, 1.0
        while p > L:
            k += 1
            p *= random.random()
        return k - 1
    else:
        return max(0, round(random.gauss(mu, math.sqrt(mu))))


def direction_with_xflip(dx, dy, dz):
    """
    Normalise a direction and randomly flip the X component with 50% probability,
    so both APA drift volumes are equally populated. Y and Z are never modified.
    """
    r = math.sqrt(dx*dx + dy*dy + dz*dz)
    if r < 1e-10:
        raise ValueError(f"Zero-length direction vector ({dx}, {dy}, {dz})")
    dx, dy, dz = dx/r, dy/r, dz/r
    if random.random() < 0.5:
        dx = -dx
    return dx, dy, dz


def read_table(path):
    """
    Parse external_cosmogenics_table.dat into
    {pdg: {'n', 'e_bins', 'e_cum', 'a_bins', 'a_cum', 'raw'}}, where the *_cum
    lists are cumulative counts for inverse-transform sampling.
    """
    species, cur = {}, None
    with open(path) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            tok = line.split()
            if tok[0] == 'SPECIES':
                cur = {'n': int(tok[2]), 'e_bins': [], 'a_bins': [],
                       'raw': [], 'lines': []}
                species[int(tok[1])] = cur
            elif tok[0] == 'L':
                cur['lines'].append((float(tok[1]), int(tok[2])))
            elif tok[0] == 'E':
                cur['e_bins'].append((float(tok[1]), float(tok[2]), int(tok[3])))
            elif tok[0] == 'A':
                cur['a_bins'].append((float(tok[1]), float(tok[2]),
                                      float(tok[3]), float(tok[4]), int(tok[5])))
            elif tok[0] == 'RAW':
                cur['raw'].append((float(tok[1]), float(tok[2]),
                                   float(tok[3]), float(tok[4])))
            else:
                raise ValueError(f"unrecognised line in {path}: {line}")

    for sp in species.values():
        # One cumulative over lines then continuum bins, so a draw picks
        # between the two in the right proportion.
        sp['e_all'] = ([(e, e, c) for e, c in sp['lines']] + sp['e_bins'])
        for key, bins in (('e_cum', sp['e_all']), ('a_cum', sp['a_bins'])):
            cum, run = [], 0
            for b in bins:
                run += b[-1]
                cum.append(run)
            sp[key] = cum
    return species


def _pick(cum):
    """Index of a bin drawn in proportion to its count."""
    return bisect.bisect_right(cum, random.random() * cum[-1])


def sample_particle(sp):
    """Draw one (ekin_keV, dx, dy, dz) in TABLE coordinates from one species."""
    if sp['raw']:
        ekin, dx, dy, dz = random.choice(sp['raw'])
        return ekin, dx, dy, dz

    # Energy: an exact line, or log-uniform inside the chosen continuum bin.
    lo, hi, _ = sp['e_all'][_pick(sp['e_cum'])]
    ekin = lo if hi == lo else 10.0 ** random.uniform(math.log10(lo), math.log10(hi))

    # Direction: uniform inside the chosen (cos_theta, phi) cell.
    ct_lo, ct_hi, ph_lo, ph_hi, _ = sp['a_bins'][_pick(sp['a_cum'])]
    ct = random.uniform(ct_lo, ct_hi)
    phi = random.uniform(ph_lo, ph_hi)
    st = math.sqrt(max(0.0, 1.0 - ct*ct))
    return ekin, st*math.cos(phi), st*math.sin(phi), ct


def kinetic_to_4mom(pdg, ekin_gev, dx, dy, dz):
    """Return (px, py, pz, E, mass_gev) given PDG, kinetic energy (GeV) and direction."""
    mass = get_mass(pdg)
    E    = ekin_gev + mass
    p    = math.sqrt(max(E*E - mass*mass, 0.0))
    return p*dx, p*dy, p*dz, E, mass


def main():
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument('input_table',   help='Sampling table from make_external_cosmogenics_table.py')
    parser.add_argument('output_hepevt', help='Output HEPEVT file for TextFileGen')
    parser.add_argument('--norm-ktondays',   type=float, default=5980.,
                        help='Exposure the table is normalised to (kTon·days) [default: 5980]')
    parser.add_argument('--target-ktondays', type=float, default=36500.,
                        help='Target exposure (kTon·days) [default: 36500 ≈ 100 kTon·years]')
    parser.add_argument('--seed', type=int, default=None,
                        help='Random seed for reproducibility (default: unseeded)')
    args = parser.parse_args()

    if args.seed is not None:
        random.seed(args.seed)

    scale = args.target_ktondays / args.norm_ktondays
    print(f"Scale factor        : {scale:.4f}  "
          f"({args.target_ktondays:.0f} / {args.norm_ktondays:.0f} kTon·days)")

    species = read_table(args.input_table)
    n_source = sum(sp['n'] for sp in species.values())

    species_count = {}
    n_written = 0

    with open(args.output_hepevt, 'w') as fout:
        for pdg, sp in sorted(species.items(), key=lambda kv: -kv[1]['n']):
            for _ in range(poisson(sp['n'] * scale)):
                n_written += 1
                ekin_kev, tdx, tdy, tdz = sample_particle(sp)
                ekin = ekin_kev / 1.0e6                 # keV -> GeV
                # Table coords: x=beam, y=vertical, z=drift
                # LArSoft coords: x=drift, y=vertical, z=beam  -> swap x<->z
                dx, dy, dz = direction_with_xflip(tdz, tdy, tdx)
                x = X_ENTRY
                y = random.uniform(Y_LO, Y_HI)
                z = random.uniform(Z_LO, Z_HI)
                px, py, pz, E, mass = kinetic_to_4mom(pdg, ekin, dx, dy, dz)

                # HEPEVT format (TextFileGen):
                #   event_number  n_particles
                #   status pdg m1 m2 d1 d2  px py pz E mass  x y z t
                # %.17g, not %.6e: HEPEVT stores TOTAL energy, and a thermal
                # neutron's kinetic energy is ~1e-15 GeV against a 0.94 GeV mass.
                # At 7 significant digits that difference rounds away entirely and
                # the particle arrives at G4 at rest -- silently losing every
                # neutron below ~0.1 keV, 9.3% of them in the reference sample.
                fout.write(f"{n_written} 1\n")
                fout.write(
                    f"1 {pdg} 0 0 0 0 "
                    f"{px:.17g} {py:.17g} {pz:.17g} {E:.17g} {mass:.17g} "
                    f"{x:.4f} {y:.4f} {z:.4f} 0.0\n"
                )
                species_count[pdg] = species_count.get(pdg, 0) + 1

    print(f"Source particles    : {n_source}")
    print(f"Expected events out : ~{n_source * scale:.0f}")
    print(f"Written events      : {n_written}  (Poisson fluctuation)")
    print(f"Output              : {args.output_hepevt}")
    print("Species breakdown:")
    for pdg, count in sorted(species_count.items(), key=lambda x: -x[1]):
        label = _LABEL.get(pdg, f'PDG={pdg}')
        print(f"  {label:14s}: {count:8d}  ({100*count/n_written:.1f}%)")


if __name__ == '__main__':
    main()
