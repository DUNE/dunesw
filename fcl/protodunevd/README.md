Note on PDVD simulation and data reconstruction workflows

# Data:

The default offline reconstruction scheme is divided in three stages:
- stage0: raw products decoding (trigger, TPC, PDS) up to hits + cluster3d spacepoints
- stage1: pandora + supera (input to SPINE) - dropping TPC RawDigits waveforms and Wires
- stage2: PDS + calibration

The corresponding FHICL files are:
- standard_reco_stage0_protodunevd_offline.fcl
- standard_reco_stage1_protodunevd_offline.fcl
- standard_reco_stage2_protodunevd_offline.fcl (yet to be setup)

Various specific data taking configurations were set-up hence the multiple extensions:
- CERN SPS beam: 
  - _beam.fcl  (for 1 GeV/c period 2, 0.5, 1.5, 2 and 4 GeV/c beam data - trigger offset 411 us - optimized readout window)
  - _beam2.fcl (for 1 GeV/c period 1, 3, 5 and 8 GeV/c beam data - trigger offset 5000 us - wide readout window)
  - _beam_tdeonly.fcl (when data streamed through TDE-DAQ - not DUNE-DAQ)
- Neutrino trigger: _neutrino.fcl
- TDE DAQ: _tdedaq.fcl (data not streamed through the usual DUNE-DAQ pipeline)
- HV scan: _hvXXX.fcl (XXX = high voltage in kV)

# Simulation:

The default PDS+CRP+CRT simulation and reconstruction chain makes use of
- gen_protodunevd_muon_1GeV.fcl
- protodunevd_g4_stage1.fcl
- protodunevd_g4_stage2.fcl
- protodunevd_detsim.fcl
- standard_reco_stage0_protodunevd_sim.fcl
- standard_reco_stage1_protodunevd_sim.fcl

Other configuration are available by default:

| No PDS                            | PDS with Xe dopping               | SCE                                | 3 ms electron lifetime                          |
|---                                |---                                |---                                 |---                                              |
| gen_protodunevd_muon_1GeV.fcl     | gen_protodunevd_muon_1GeV.fcl     | gen_protodunevd_muon_1GeV.fcl      | gen_protodunevd_muon_1GeV.fcl                   |
| protodunevd_g4_stage1.fcl         | protodunevd_g4_stage1.fcl         | protodunevd_g4_stage1.fcl          | protodunevd_g4_stage1.fcl                       |
| protodunevd_g4_stage2_nopds.fcl   | protodunevd_g4_stage2.fcl         | protodunevd_g4_stage2_sce_E500.fcl | protodunevd_g4_stage2.fcl                       |
|                                   | protodunevd_g4_stage3_Xe10ppm.fcl |                                    |                                                 |
| protodunevd_detsim_nopds.fcl      | protodunevd_detsim_Xe10ppm.fcl    | protodunevd_detsim.fcl             | protodunevd_detsim_nodiffusion_03mslifetime.fcl |
| protodunevd_reco_nopds.fcl        | protodunevd_reco.fcl              | protodunevd_MC_reco_sce_E500.fcl   | protodunevd_reco.fcl                            |
