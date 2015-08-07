
# simple examples using prodsingle

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

