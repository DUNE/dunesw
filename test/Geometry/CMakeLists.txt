
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

cet_test(geometry_dune35t HANDBUILT
  DATAFILES test_geometry_dune35t.fcl
  TEST_EXEC lar
  TEST_ARGS --rethrow-all --config ./test_geometry_dune35t.fcl
)


simple_plugin ( GeometryTest35 "module"
                     larcore_Geometry
                     larcore_Geometry_Geometry_service
		     ${ART_FRAMEWORK_CORE}
   		     ${ART_FRAMEWORK_PRINCIPAL}
		     ${ART_FRAMEWORK_SERVICES_REGISTRY}
		     ${ART_FRAMEWORK_SERVICES_BASIC}
		     ${ART_FRAMEWORK_SERVICES_OPTIONAL}
		     ${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILESERVICE_SERVICE}
             	     ${ART_FRAMEWORK_SERVICES_OPTIONAL_RANDOMNUMBERGENERATOR_SERVICE}
		     ${ART_PERSISTENCY_COMMON}
		     ${ART_PERSISTENCY_PROVENANCE}
		     ${ART_UTILITIES}
                     ${MF_MESSAGELOGGER}
                     ${MF_UTILITIES}
                     ${FHICLCPP}
                     ${CETLIB}
                     ${ROOT_BASIC_LIB_LIST}

               BASENAME_ONLY
          )


#
# the following are tests equivalent to the module ones, but with no framework
#
# unit test (use the hard-coded configuration for DUNE 35t "optimized" geometry)
# this uses BOOST for the test
cet_test(geometry_iterator_dune35t_test
  SOURCES geometry_iterator_dune35t_test.cxx
  LIBRARIES larcore_Geometry
            GeometryTestLib
            dune_Geometry
            ${MF_MESSAGELOGGER}
            ${MF_UTILITIES}
            ${FHICLCPP}
            ${CETLIB}
  USE_BOOST_UNIT
)

# unit test (use the hard-coded configuration for DUNE Far Detector geometry)
# this uses BOOST for the test
cet_test(geometry_iterator_dunefd_test
  SOURCES geometry_iterator_dunefd_test.cxx
  LIBRARIES larcore_Geometry
            GeometryTestLib
            dune_Geometry
            ${MF_MESSAGELOGGER}
            ${MF_UTILITIES}
            ${FHICLCPP}
            ${CETLIB}
  USE_BOOST_UNIT
)


# unit test (use the hard-coded configuration for DUNE 35t "optimized" geometry)
cet_test(geometry_dune35t_test
  SOURCES geometry_dune35t_test.cxx
  DATAFILES test_geometry_dune35t.fcl
  TEST_ARGS ./test_geometry_dune35t.fcl
  LIBRARIES larcore_Geometry
            GeometryTestLib
            dune_Geometry
            ${MF_MESSAGELOGGER}
            ${MF_UTILITIES}
            ${FHICLCPP}
            ${CETLIB}
)

# unit test (use the hard-coded configuration for DUNE Far Detector geometry)
cet_test(geometry_dunefd_test
  SOURCES geometry_dunefd_test.cxx
  DATAFILES test_geometry_dunefd.fcl
  TEST_ARGS ./test_geometry_dunefd.fcl
  LIBRARIES larcore_Geometry
            GeometryTestLib
            dune_Geometry
            ${MF_MESSAGELOGGER}
            ${MF_UTILITIES}
            ${FHICLCPP}
            ${CETLIB}
)


# unit test (use the hard-coded configuration for DUNE 35t "optimized" geometry)
cet_test(geometry_iterator_loop_dune35t_test
  SOURCES geometry_iterator_loop_dune35t_test.cxx
  LIBRARIES larcore_Geometry
            GeometryTestLib
            dune_Geometry
            ${MF_MESSAGELOGGER}
            ${MF_UTILITIES}
            ${FHICLCPP}
            ${CETLIB}
)

# unit test (use the hard-coded configuration for DUNE Far Detector geometry)
cet_test(geometry_iterator_loop_dunefd_test
  SOURCES geometry_iterator_loop_dunefd_test.cxx
  LIBRARIES larcore_Geometry
            GeometryTestLib
            dune_Geometry
            ${MF_MESSAGELOGGER}
            ${MF_UTILITIES}
            ${FHICLCPP}
            ${CETLIB}
)
