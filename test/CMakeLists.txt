# various integration tests

include(CetTest)

cet_enable_asserts()

add_subdirectory(daqinput35t)
add_subdirectory(EventGenerator)
add_subdirectory(Geometry)
add_subdirectory(ci)
add_subdirectory(OpDet)

# these tests run a FCL file and fail only if lar exits with a bad exit code;
# they are fast and always run.
# FCL files need to be copied to the test area (DATAFILES directive) since they
# are not installed.
# OPTIONAL_GROUPS is set to execute the test in the "BROKEN" test suite;
# that is because this test is currently failing for MicroBooNE
cet_test(donothing_dune35t HANDBUILT
  DATAFILES test_donothing_dune35t.fcl
  TEST_EXEC lar
  TEST_ARGS --rethrow-all --config ./test_donothing_dune35t.fcl
)
cet_test(donothing_simul_dune35t HANDBUILT
  DATAFILES test_donothing_simul_dune35t.fcl
  TEST_EXEC lar
  TEST_ARGS --rethrow-all --config ./test_donothing_simul_dune35t.fcl
)
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
