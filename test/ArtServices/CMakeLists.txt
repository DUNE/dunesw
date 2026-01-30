cet_test(test_Geometry SOURCE test_Geometry.cxx
  LIBRARIES
    dunecore::ArtSupport
    larcore::headers
    art::Framework_Services_Registry
    larcorealg::Geometry
    ROOT::Core
    cetlib::cetlib cetlib_except::cetlib_except
)

# disable tests that depend on LegacyLArG4
#cet_test(test_DetectorClocksService SOURCE test_DetectorClocksService.cxx
#  LIBRARIES
#    dunecore::ArtSupport
#    lardata::Utilities
#    art::Framework_Services_Registry
#    ROOT::Core
#    cetlib::cetlib cetlib_except::cetlib_except
#)

#cet_test(test_DetectorProperties SOURCE test_DetectorProperties.cxx
#  LIBRARIES
#    dunecore::ArtSupport
#    lardata::Utilities
#    art::Framework_Services_Registry
#    lardataalg::DetectorInfo
#    ROOT::Core
#    cetlib::cetlib cetlib_except::cetlib_except
#)

#cet_test(test_LArProperties SOURCE test_LArProperties.cxx
#  LIBRARIES
#    dunecore::ArtSupport
#    lardata::Utilities
#    art::Framework_Services_Registry
#    ROOT::Core
#    cetlib::cetlib cetlib_except::cetlib_except
#)

cet_test(test_LArSeedService SOURCE test_LArSeedService.cxx
  LIBRARIES
    nurandom::RandomUtils_NuRandomService_service
    dunecore::ArtSupport
    art::Framework_Services_Registry
    ROOT::Core
    cetlib::cetlib cetlib_except::cetlib_except
)

cet_test(test_SignalShapingServiceDUNE SOURCE test_SignalShapingServiceDUNE.cxx
  LIBRARIES
    dunecore::SignalShapingServiceDUNE_service
    dunecore::ArtSupport
    art::Framework_Services_Registry
    lardata::Utilities
    ROOT::Core
    cetlib::cetlib cetlib_except::cetlib_except
)

install_source()
