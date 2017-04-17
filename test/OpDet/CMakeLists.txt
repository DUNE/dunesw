
# OpDet test on DUNE geometries

#
# This test simply runs testgeo.sh script.
#
# PREBUILT means that we provide the executable and cmake hasn't to create it
# (like for external executables, e.g. lar, and scripts); this executable will
# be installed in the package if INSTALL_BIN is specified
# OPTIONAL_GROUPS is not defined, or else this test would not be run by default
# (use mrb t --test-all to run all the tests anyway)
# cet_test(testgeo.sh PREBUILT
#   testgeo.sh
# )

# these tests run a FCL file and fail only if lar exits with a bad exit code;
# they are fast and always run.
# FCL files need to be copied to the test area (DATAFILES directive) since they
# are not installed.

# FIXME the unit tests optical_sim_dune35t, optical_digi_dune35t,
# optical_reco_dune35t and build_oplib_dune35t
# crash with a SEGFAULT on Mac OS,
# they will be executed only on SLF for now
if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   cet_test(optical_sim_dune35t HANDBUILT
     DATAFILES test_optical_sim_dune35t.fcl
     TEST_EXEC lar
     TEST_ARGS --rethrow-all --config ./test_optical_sim_dune35t.fcl 
   )

   cet_test(optical_digi_dune35t HANDBUILT
     DATAFILES test_optical_digi_dune35t.fcl
     TEST_EXEC lar
     TEST_ARGS --rethrow-all --config ./test_optical_digi_dune35t.fcl 
   )

   cet_test(optical_reco_dune35t HANDBUILT
     DATAFILES test_optical_reco_dune35t.fcl
     TEST_EXEC lar
     TEST_ARGS --rethrow-all --config ./test_optical_reco_dune35t.fcl 
   )

   cet_test(build_oplib_dune35t HANDBUILT
     DATAFILES test_build_oplib_dune35t.fcl
     TEST_EXEC lar
     TEST_ARGS --rethrow-all --config ./test_build_oplib_dune35t.fcl 
   )
endif()
