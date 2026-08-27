# various integration tests

include(CetTest)

cet_transitive_paths(FHICL_DIR BINARY IN_TREE)
cet_test_env_prepend(FHICL_FILE_PATH "." ${TRANSITIVE_PATHS_WITH_FHICL_DIR} ${PACKAGE_BINARY_PATH}/fcl ${PROJECT_BINARY_DIR}/../dunesim/fcl ${PROJECT_BINARY_DIR}/../duneopdet/fcl ${PROJECT_BINARY_DIR}/../dunecalib/fcl ${PROJECT_BINARY_DIR}/../duneprototypes/fcl ${PROJECT_BINARY_DIR}/../dunedataprep/fcl)
cet_transitive_paths(LIBRARY_DIR BINARY IN_TREE)
cet_test_env_prepend(CET_PLUGIN_PATH ${TRANSITIVE_PATHS_WITH_LIBRARY_DIR} ${PROJECT_BINARY_DIR}/../duneopdet/lib)
cet_transitive_paths(GDML_DIR BINARY IN_TREE)
cet_test_env_prepend(FW_SEARCH_PATH ${TRANSITIVE_PATHS_WITH_GDML_DIR} ${PROJECT_BINARY_DIR}/../dunecore/gdml)

cet_enable_asserts()

#add_subdirectory(daqinput35t)
add_subdirectory(EventGenerator)
add_subdirectory(Geometry)
add_subdirectory(ci)
#add_subdirectory(OpDet)

add_subdirectory(ArtServices)

# these tests run a FCL file and fail only if lar exits with a bad exit code;
# they are fast and always run.
# FCL files need to be copied to the test area (DATAFILES directive) since they
# are not installed.
# OPTIONAL_GROUPS is set to execute the test in the "BROKEN" test suite;
# that is because this test is currently failing for MicroBooNE

# FIXME the unit tests donothing_dune35t and donothing_simul_dune35t
# crash with a SEGFAULT on Mac OS,
# they will be executed only on SLF for now

#if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#   cet_test(donothing_dune35t HANDBUILT
#     DATAFILES test_donothing_dune35t.fcl
#     TEST_EXEC lar
#     TEST_ARGS --rethrow-all --config ./test_donothing_dune35t.fcl
#   )
#   cet_test(donothing_simul_dune35t HANDBUILT
#     DATAFILES test_donothing_simul_dune35t.fcl
#     TEST_EXEC lar
#     TEST_ARGS --rethrow-all --config ./test_donothing_simul_dune35t.fcl
#   )
#endif()

cet_test(donothing_dunefd HANDBUILT
  DATAFILES test_donothing_dunefd.fcl
  TEST_EXEC lar
  TEST_ARGS --rethrow-all --config ./test_donothing_dunefd.fcl
)
cet_test(donothing_simul_dunefd HANDBUILT
  DATAFILES test_donothing_simul_dunefd.fcl
  TEST_EXEC lar
  TEST_ARGS --rethrow-all --config ./test_donothing_simul_dunefd.fcl
)
