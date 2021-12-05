set( IFDH_ART_DIR $ENV{IFDH_ART_DIR} )

add_subdirectory(DuneExample)
add_subdirectory(DuneObj)
add_subdirectory(DuneObjDumpers)
add_subdirectory(ArtSupport)
add_subdirectory(DuneInterface)
include(dune::ToolTypes) # Enable simpler building of tools.
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
add_subdirectory(EnergyStudies)
add_subdirectory(AnaTree)
add_subdirectory(HitFinderDUNE)
add_subdirectory(TrackFinderDUNE)
add_subdirectory(HDF5Utils)
add_subdirectory(DUNEPandora)
add_subdirectory(SimFilter)
add_subdirectory(FDSensOpt)
add_subdirectory(TrackingAna)
add_subdirectory(ShowerAna)
add_subdirectory(HitAnalysis)
add_subdirectory(EventFilters)
add_subdirectory(ClusterFinderDUNE)
add_subdirectory(RecoAlgDUNE)
add_subdirectory(Protodune)
add_subdirectory(DAQTriggerSim)
add_subdirectory(SpaceCharge)
add_subdirectory(SpaceChargeServices)
add_subdirectory(SupernovaAna)
#add_subdirectory(DataOverlay)
add_subdirectory(DAQSimAna)
add_subdirectory(3x1x1dp)
add_subdirectory(CVN)
add_subdirectory(BeamData)
add_subdirectory(Calib)
add_subdirectory(CalibServices)
add_subdirectory(CAFMaker)
add_subdirectory(RegCNN)
add_subdirectory(Iceberg)
add_subdirectory(DUNEWireCell)
add_subdirectory(APAIO)
add_subdirectory(ProductFilters)
add_subdirectory(AnaUtils)
add_subdirectory(TrackPID)
add_subdirectory(PandoraAnalysis)
add_subdirectory(InfillChannels)
add_subdirectory(VLNets)
add_subdirectory(Coldbox)

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
#     "larsim_Simulation nug4::ParticleNavigation lardataobj_Simulation",
#     "larsim_MCCheater",
#     "larreco_Calorimetry",
#     "lardata_RecoObjects",
#     "larreco_RecoAlg",
#     "larsim_LegacyLArG4",
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
