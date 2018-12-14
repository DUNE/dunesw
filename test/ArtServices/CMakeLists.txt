cet_test(test_Geometry SOURCES test_Geometry.cxx
  LIBRARIES
    dune_ArtSupport
    larcorealg_Geometry
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
