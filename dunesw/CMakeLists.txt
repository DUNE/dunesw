add_subdirectory(Geometry)
add_subdirectory(Utilities)
add_subdirectory(Simulation)
add_subdirectory(LArG4)
add_subdirectory(PhotonPropagation)
add_subdirectory(OpticalDetector)  
add_subdirectory(DetSim)
add_subdirectory(EventGenerator)
add_subdirectory(CalData)
add_subdirectory(RawdataDisplay)
add_subdirectory(EnergyStudies)
add_subdirectory(AnaTree)
add_subdirectory(daqinput35t)
add_subdirectory(OnlineMonitor)
add_subdirectory(HitFinderDUNE)
add_subdirectory(TrackFinderDUNE)
add_subdirectory(DUNEPandora)
add_subdirectory(CTree)
add_subdirectory(T0Reco)
add_subdirectory(SimFilter)
add_subdirectory(FDSensOpt)

# Respect the order specified in lar_build, which is:
#
#     "SoftRelTools",
#     "SRT_LAR",
#     "SimpleTypesAndConstants",
#     "Geometry",
#     "SummaryData",
#     "RawData",
#     "RecoBase",
#     "OpticalDetectorData",
#     "AnalysisBase",
#     "Utilities",
#     "Simulation",
#     "MCCheater",
#     "AnalysisAlg",
#     "RecoObjects",
#     "RecoAlg",
#     "LArG4",
#     "PhotonPropagation",
#     "DetSim",
#     "EventGenerator",
#     "Filters",
#     "CalData",
#     "ClusterFinder",
#     "Genfit",
#     "HitFinder",
#     "TrackFinder",
#     "VertexFinder",
#     "EventFinder",
#     "TriggerAlgo",
#     "OpticalDetector",
#     "Calorimetry", 
#     "ShowerFinder",
#     "EventDisplay",
#     "ParticleIdentification",
#     "AnalysisExample",
#     "LArPandoraAlgorithms",
#     "LArPandoraInterface"

