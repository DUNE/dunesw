# Low-energy cosmogenics generators

Two independent samples of cosmogenic activity in the DUNE FD HD:

* **Internal** — isotopes produced by muon spallation on 40Ar that beta-decay inside the active volume. `SingleGen` places one of 44 isotope species at rest uniformly in the LAr.
* **External** — mostly gammas and neutrons produced in the surrounding rock, injected at the central APA plane through `TextFileGen`.


## The external sampling table

`external_cosmogenics_to_hepevt.py` builds its HEPEVT file from
`external_cosmogenics_table.dat`. `make_external_cosmogenics_table.py` produces it.

The current table is a reduction which does not include correlations O(0.12). Contact the LAPP group (Andres Lopez Moreno, Luis Manzanillas Velez) for the full table

## Workflow

    # external
    python external_cosmogenics_to_hepevt.py external_cosmogenics_table.dat \
        external_cosmogenics.hepevt --norm-ktondays 5980 --target-ktondays 36500

**The table is normalised to 5980 kton-days; a full 10-year module is 36500.**
Scale `--target-ktondays` to the exposure you want.

    # -n is REQUIRED. TextFileGen throws at EOF rather than ending the job, so
    # without it art aborts on the last event, never closes RootOutput, and the
    # whole gen stage is lost. The count is written beside the HEPEVT file.
    lar -c gen_external_cosmogenics_dune10kt_1x2x6.fcl \
        -n $(cat external_cosmogenics.hepevt.nevents) \
        -o external_cosmogenics_gen.root
    lar -c g4_external_cosmogenics_dune10kt_1x2x6.fcl \
        -s external_cosmogenics_gen.root -o external_cosmogenics_g4.root

    # internal (N*44 events gives ~N per species. The example uses 1K of each, but tune to your leisure)
    lar -c gen_internal_cosmogenics_dune10kt_1x2x6.fcl -n 4400 \
        -o internal_cosmogenics_gen.root
    lar -c g4_internal_cosmogenics_dune10kt_1x2x6.fcl \
        -s internal_cosmogenics_gen.root -o internal_cosmogenics_g4.root

`TextFileGen` opens `InputFileName` with a plain `ifstream` and does not search
`FW_SEARCH_PATH`, so the gen stage must run from the directory holding the
HEPEVT file, or the FCL must be overridden with an absolute path.

## Geometry envelope

Both generators cover the full active volume of
`dune10kt_v6_refactored_1x2x6.gdml`: x +-363.4 cm, **y +-600.0 cm**, z 0-1393.5 cm.
The 1x2x6 stacks two 600 cm APAs vertically, so the active height is 1200 cm.
Assuming a single 610 cm APA -- as an earlier revision of these files did --
confines the source to the middle half of the detector and biases every rate
normalised per unit active volume by a factor of about two.
