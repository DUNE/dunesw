cet_test(test_Geometry SOURCES test_Geometry.cxx
  LIBRARIES
    dunecore_ArtSupport
    ART_FRAMEWORK_SERVICES_REGISTRY
    art::Utilities canvas
    larcorealg_Geometry
    ROOT_BASIC_LIB_LIST
    cetlib::cetlib cetlib_except
)

cet_test(test_DetectorClocksService SOURCES test_DetectorClocksService.cxx
  LIBRARIES
    dunecore_ArtSupport
    ART_FRAMEWORK_SERVICES_REGISTRY
    art::Utilities canvas
    ROOT_BASIC_LIB_LIST
    cetlib::cetlib cetlib_except
)

cet_test(test_DetectorProperties SOURCES test_DetectorProperties.cxx
  LIBRARIES
    dunecore_ArtSupport
    ART_FRAMEWORK_SERVICES_REGISTRY
    lardataalg_DetectorInfo
    art::Utilities canvas
    ROOT_BASIC_LIB_LIST
    cetlib::cetlib cetlib_except
)

cet_test(test_LArProperties SOURCES test_LArProperties.cxx
  LIBRARIES
    dunecore_ArtSupport
    ART_FRAMEWORK_SERVICES_REGISTRY
    art::Utilities canvas
    ROOT_BASIC_LIB_LIST
    cetlib::cetlib cetlib_except
)

cet_test(test_LArSeedService SOURCES test_LArSeedService.cxx
  LIBRARIES
    nurandom::RandomUtils_NuRandomService_service
    dunecore_ArtSupport
    ART_FRAMEWORK_SERVICES_REGISTRY
    art::Utilities canvas
    ROOT_BASIC_LIB_LIST
    cetlib::cetlib cetlib_except
)

cet_test(test_SignalShapingServiceDUNE SOURCES test_SignalShapingServiceDUNE.cxx
  LIBRARIES
    dunecore::SignalShapingServiceDUNE_service
    dunecore_ArtSupport
    ART_FRAMEWORK_SERVICES_REGISTRY
    art::Utilities canvas
    lardata_Utilities
    ROOT_BASIC_LIB_LIST
    cetlib::cetlib cetlib_except
)

install_source()
