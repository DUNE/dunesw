cet_test(test_Geometry SOURCES test_Geometry.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Framework_Services_Registry
    larcorealg::Geometry
    ROOT::Core
    cetlib::cetlib cetlib_except
)

cet_test(test_DetectorClocksService SOURCES test_DetectorClocksService.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Framework_Services_Registry
    ROOT::Core
    cetlib::cetlib cetlib_except
)

cet_test(test_DetectorProperties SOURCES test_DetectorProperties.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Framework_Services_Registry
    lardataalg_DetectorInfo
    ROOT::Core
    cetlib::cetlib cetlib_except
)

cet_test(test_LArProperties SOURCES test_LArProperties.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Framework_Services_Registry
    ROOT::Core
    cetlib::cetlib cetlib_except
)

cet_test(test_LArSeedService SOURCES test_LArSeedService.cxx
  LIBRARIES
    nurandom::RandomUtils_NuRandomService_service
    dunecore::ArtSupport
    art::Framework_Services_Registry
    ROOT::Core
    cetlib::cetlib cetlib_except
)

cet_test(test_SignalShapingServiceDUNE SOURCES test_SignalShapingServiceDUNE.cxx
  LIBRARIES
    dunecore::SignalShapingServiceDUNE_service
    dunecore::ArtSupport
    art::Framework_Services_Registry
    lardata::Utilities
    ROOT::Core
    cetlib::cetlib cetlib_except
)

install_source()
