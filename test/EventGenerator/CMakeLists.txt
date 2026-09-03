
# simple examples using prodsingle
cet_transitive_paths(FHICL_DIR BINARY IN_TREE)
cet_test_env_prepend(FHICL_FILE_PATH "." ${TRANSITIVE_PATHS_WITH_FHICL_DIR} ${PACKAGE_BINARY_DIR}/fcl ${PROJECT_BINARY_DIR}/../dunecalib/fcl ${PROJECT_BINARY_DIR}/../dunesim/fcl ${PROJECT_BINARY_DIR}/../duneopdet/fcl ${PROJECT_BINARY_DIR}/../dunedataprep_/fcl ${PROJECT_BINARY_DIR}/../duneprototypes/fcl)
cet_transitive_paths(LIBRARY_DIR BINARY IN_TREE)
cet_test_env_prepend(CET_PLUGIN_PATH ${TRANSITIVE_PATHS_WITH_LIBRARY_DIR})


# use the general prodsingle_dune35t.fcl file
# because OPTIONAL_GROUPS is defined, this test will not be run by default
# use mrb t --test-all to run all the tests
cet_test(prodsingle_dune35t HANDBUILT
  TEST_EXEC lar
  TEST_ARGS --rethrow-all --config prodsingle_dune35t.fcl
  OPTIONAL_GROUPS RELEASE
)

# same thing for the full detector geometry
cet_test(prodsingle_dunefd HANDBUILT
  TEST_EXEC lar
  TEST_ARGS --rethrow-all --config prodsingle_dunefd.fcl
  OPTIONAL_GROUPS RELEASE
)

