# geometry test on DUNE geometries

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
cet_test(geometry_dunefd HANDBUILT
  DATAFILES test_geometry_dunefd.fcl
  TEST_EXEC lar
  TEST_ARGS --rethrow-all --config ./test_geometry_dunefd.fcl
)

#cet_test(geometry_dunedphase10kt HANDBUILT
#  DATAFILES test_geometry_dunedphase10kt.fcl
#  TEST_EXEC lar
#  TEST_ARGS --rethrow-all --config ./test_geometry_dunedphase10kt.fcl
#)

#cet_test(geometry_dunedphase10kt_workspace HANDBUILT
#  DATAFILES test_geometry_dunedphase10kt_workspace.fcl
#  TEST_EXEC lar
#  TEST_ARGS --rethrow-all --config ./test_geometry_dunedphase10kt_workspace.fcl
#)


cet_test(geometry_iterator_loop_dunefd HANDBUILT
  DATAFILES test_geometry_iterator_loop_dunefd.fcl
  TEST_EXEC lar
  TEST_ARGS --rethrow-all --config ./test_geometry_iterator_loop_dunefd.fcl
)


#
# the following are tests equivalent to the module ones, but with no framework
#

# test for CRM channel mapping (BOOST unit test)
cet_test(geometry_crmchannelmapping_test
  SOURCES geometry_crmchannelmapping_test.cxx
  LIBRARIES larcorealg_Geometry
            dune_Geometry
            messagefacility::MF_MessageLogger
            larcorealg::GeometryTestLib
            ART_FRAMEWORK_SERVICES_REGISTRY
            art_Utilities canvas
            ROOT_BASIC_LIB_LIST
            FHICLCPP
            cetlib cetlib_except
  USE_BOOST_UNIT
  DATAFILES test_geometry_dunedphase10kt.fcl
  TEST_ARGS -- ./test_geometry_dunedphase10kt.fcl
)


cet_test(dump_channel_map_dunefd_test HANDBUILT
  DATAFILES dump_dunefd_channelmap.fcl
  TEST_EXEC lar
  TEST_ARGS --rethrow-all --config ./dump_dunefd_channelmap.fcl
)

cet_test(dump_channel_map_dunedphase10kt_test HANDBUILT
  DATAFILES dump_dunedphase10kt_channelmap.fcl
  TEST_EXEC lar
  TEST_ARGS --rethrow-all --config ./dump_dunedphase10kt_channelmap.fcl
)

cet_test(dump_channel_map_dunedphase10kt_workspace_test HANDBUILT
  DATAFILES dump_dunedphase10kt_workspace_channelmap.fcl
  TEST_EXEC lar
  TEST_ARGS --rethrow-all --config ./dump_dunedphase10kt_workspace_channelmap.fcl
)
