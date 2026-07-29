cet_transitive_paths(FHICL_DIR BINARY IN_TREE)
cet_test_env_prepend(FHICL_FILE_PATH "." ${TRANSITIVE_PATHS_WITH_FHICL_DIR} ${PROJECT_BINARY_DIR}/../dunesim/fcl ${PROJECT_BINARY_DIR}/../duneopdet/fcl ${PROJECT_BINARY_DIR}/../dunecalib/fcl ${PROJECT_BINARY_DIR}/../duneprototypes/fcl ${PROJECT_BINARY_DIR}/../dunedataprep/fcl)
cet_transitive_paths(LIBRARY_DIR BINARY IN_TREE)
cet_test_env_prepend(CET_PLUGIN_PATH ${TRANSITIVE_PATHS_WITH_LIBRARY_DIR} ${PROJECT_BINARY_DIR}/../dunesim/lib)
cet_transitive_paths(GDML_DIR BINARY IN_TREE)
cet_test_env_prepend(FW_SEARCH_PATH ${TRANSITIVE_PATHS_WITH_GDML_DIR})

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
