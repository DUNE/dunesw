set( IFDH_ART_DIR $ENV{IFDH_ART_DIR} )

add_subdirectory(DuneObj)
add_subdirectory(DuneObjDumpers)
add_subdirectory(ArtSupport)
add_subdirectory(DuneInterface)
add_subdirectory(DuneServiceAccess)
add_subdirectory(DuneCommon)
add_subdirectory(Geometry)
add_subdirectory(Utilities)
add_subdirectory(Simulation)
add_subdirectory(LArG4)
add_subdirectory(PhotonPropagation)
add_subdirectory(OpticalDetector)  
add_subdirectory(DetSim)
add_subdirectory(DetectorVariations)
add_subdirectory(EventGenerator)
add_subdirectory(Daq)
add_subdirectory(CalData)
add_subdirectory(DataPrep)
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
add_subdirectory(Gaps)
add_subdirectory(TrackingAna)
add_subdirectory(ShowerAna)
add_subdirectory(RunHistory)
add_subdirectory(NearlineMonitor)
add_subdirectory(MuonCounters)
add_subdirectory(MuonCounterTimes)
add_subdirectory(HitAnalysis)
add_subdirectory(EventFilters)
add_subdirectory(ClusterFinderDUNE)
add_subdirectory(RecoAlgDUNE)
add_subdirectory(Protodune)
add_subdirectory(DAQTriggerSim)
add_subdirectory(SpaceCharge)
add_subdirectory(SpaceChargeServices)
add_subdirectory(SupernovaAna)
add_subdirectory(DataOverlay)
#add_subdirectory(DAQSimAna)
add_subdirectory(3x1x1dp)
add_subdirectory(CVN)
add_subdirectory(BeamData)
add_subdirectory(Calib)
add_subdirectory(CalibServices)
add_subdirectory(CAFMaker)

add_subdirectory(RegCVN)

# Respect the order specified in lar_build, which is:
#
#     "SoftRelTools",
#     "SRT_LAR",
#     "SimpleTypesAndConstants",
#     "larcorealg_Geometry",
#     "larcoreobj_SummaryData",
#     "lardataobj_RawData",
#     "lardataobj_RecoBase",
#     "lardataobj_OpticalDetectorData",
#     "lardataobj_AnalysisBase",
#     "lardata_Utilities",
#     "larsim_Simulation nutools_ParticleNavigation lardataobj_Simulation",
#     "larsim_MCCheater",
#     "larreco_Calorimetry",
#     "lardata_RecoObjects larreco_Deprecated",
#     "larreco_RecoAlg",
#     "larsim_LArG4",
#     "larsim_PhotonPropagation",
#     "larsim_DetSim",
#     "larsim_EventGenerator",
#     "larevt_Filters",
#     "CalData",
#     "larreco_ClusterFinder",
#     "larreco_Genfit",
#     "larreco_HitFinder",
#     "larreco_TrackFinder",
#     "larreco_VertexFinder",
#     "larreco_EventFinder",
#     "larsim_TriggerAlgo",
#     "larana_OpticalDetector",
#     "larreco_Calorimetry", 
#     "larreco_ShowerFinder",
#     "lareventdisplay_EventDisplay",
#     "larana_ParticleIdentification",
#     "larexamples_AnalysisExample",
#     "LArPandoraAlgorithms",
#     "larpandora_LArPandoraInterface"
