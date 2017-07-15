# art_extensions/test/services/CMakeLists.txt

cet_test(test_TFileService SOURCES test_TFileService.cxx
  LIBRARIES
    dune_ArtSupport
    art_Framework_Services_Optional_TFileService_service
    ${ART_FRAMEWORK_SERVICES_OPTIONAL}
    ${ROOT_BASIC_LIB_LIST}
)

cet_test(test_Geometry SOURCES test_Geometry.cxx
  LIBRARIES
    dune_ArtSupport
    larcorealg_Geometry
    ${ROOT_BASIC_LIB_LIST}
)

cet_test(test_RandomNumberGenerator SOURCES test_RandomNumberGenerator.cxx
  LIBRARIES
    art_Framework_Services_Optional_RandomNumberGenerator_service
    dune_ArtSupport
    ${ART_FRAMEWORK_CORE}
    ${ROOT_BASIC_LIB_LIST}
)

cet_test(test_DetectorClocksService SOURCES test_DetectorClocksService.cxx
  LIBRARIES
    dune_ArtSupport
    ${ROOT_BASIC_LIB_LIST}
)

cet_test(test_DetectorProperties SOURCES test_DetectorProperties.cxx
  LIBRARIES
    dune_ArtSupport
    art_Utilities canvas
    ${ROOT_BASIC_LIB_LIST}
)

cet_test(test_LArProperties SOURCES test_LArProperties.cxx
  LIBRARIES
    dune_ArtSupport
    ${ROOT_BASIC_LIB_LIST}
)

cet_test(test_LArSeedService SOURCES test_LArSeedService.cxx
  LIBRARIES
    nutools_RandomUtils_NuRandomService_service
    dune_ArtSupport
    ${ROOT_BASIC_LIB_LIST}
)

cet_test(test_SignalShapingServiceDUNE SOURCES test_SignalShapingServiceDUNE.cxx
  LIBRARIES
    SignalShapingServiceDUNE_service
    dune_ArtSupport
    lardata_Utilities
    ${ROOT_BASIC_LIB_LIST}
)

install_source()
