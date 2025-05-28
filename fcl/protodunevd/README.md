Note on PDVD simulation and data reconstruction workflows

# Simulation:

The default PDS+CRP+CRT simulation and reconstruction chain makes use of
- gen_protodunevd_muon_1GeV.fcl
- protodunevd_g4_stage1.fcl
- protodunevd_g4_stage2.fcl
- protodunevd_detsim.fcl
- protodunevd_reco.fcl

Other configuration are available by default:

| No PDS                            | PDS with Xe dopping               | SCE                                | 3 ms electron lifetime                          |
|---                                |---                                |---                                 |---                                              |
| gen_protodunevd_muon_1GeV.fcl     | gen_protodunevd_muon_1GeV.fcl     | gen_protodunevd_muon_1GeV.fcl      | gen_protodunevd_muon_1GeV.fcl                   |
| protodunevd_g4_stage1.fcl         | protodunevd_g4_stage1.fcl         | protodunevd_g4_stage1.fcl          | protodunevd_g4_stage1.fcl                       |
| protodunevd_g4_stage2_nopds.fcl   | protodunevd_g4_stage2.fcl         | protodunevd_g4_stage2_sce_E500.fcl | protodunevd_g4_stage2.fcl                       |
|                                   | protodunevd_g4_stage3_Xe10ppm.fcl |                                    |                                                 |
| protodunevd_detsim_nopds.fcl      | protodunevd_detsim_Xe10ppm.fcl    | protodunevd_detsim.fcl             | protodunevd_detsim_nodiffusion_03mslifetime.fcl |
| protodunevd_reco_nopds.fcl        | protodunevd_reco.fcl              | protodunevd_MC_reco_sce_E500.fcl   | protodunevd_reco.fcl                            |
