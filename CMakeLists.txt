# ======================================================================
#  larsoft main build file
#
#  cd .../path/to/build/directory
#  source .../path/to/larsoft/ups/setup_for_development <-d|-p>
#  cmake [-DCMAKE_INSTALL_PREFIX=/install/path]
#        -DCMAKE_BUILD_TYPE=$CETPKG_TYPE
#        $CETPKG_SOURCE
#  make
#  make test
#  make install
#  make package (builds distribution tarfile)
# ======================================================================
# LarSoft is an empty product
# It sets up all of the larsoft ups products (lardata, larsim, larreco, etc.)
# ======================================================================


# use cmake 2.8 or later
cmake_minimum_required (VERSION 2.8)

project(dunetpc)

# cetbuildtools contains our cmake modules
SET ( CETBUILDTOOLS_VERSION $ENV{CETBUILDTOOLS_VERSION} )
IF (NOT CETBUILDTOOLS_VERSION)
    MESSAGE (FATAL_ERROR "ERROR: setup cetbuildtools to get the cmake modules")
ENDIF()

set(CMAKE_MODULE_PATH $ENV{CANVAS_ROOT_IO_DIR}/Modules
		      $ENV{CETBUILDTOOLS_DIR}/Modules
		      ${CMAKE_MODULE_PATH})

include(CetCMakeEnv)
cet_cmake_env()

set_install_root()

cet_set_compiler_flags(DIAGS CAUTIOUS
  WERROR
  NO_UNDEFINED
  ALLOW_DEPRECATIONS
  EXTRA_FLAGS -pedantic -Wno-unused-local-typedefs  -O0
)

cet_report_compiler_flags()

# these are minimum required versions, not the actual product versions
find_ups_product( larcoreobj )
find_ups_product( larcore v1_00_00 )
find_ups_product( larevt v1_00_00 )
find_ups_product( lardataobj )
find_ups_product( lardataalg )
find_ups_product( lardata v1_00_00 )
find_ups_product( larpandora v1_00_00 )
find_ups_product( pandora )
find_ups_product( larreco v1_00_00 )
find_ups_product( larana v1_00_00 )
find_ups_product( nutools v1_00_00 )
find_ups_product( art v1_09_00 )
find_ups_product( clhep v2_1_3_0 )
find_ups_product( messagefacility v1_10_00 )
find_ups_product( cetbuildtools v3_10_00 )
find_ups_product( postgresql v9_1_5 )
find_ups_product( lbne_raw_data v0_00_02 )
find_ups_product( dune_raw_data v1_10_00 )
find_ups_product( dunepdsprce v0_0_3 )
find_ups_product( artdaq_core v01_03_6 )
find_ups_product( ifdh_art )
find_ups_geant4( geant4 )
find_ups_product( systematicstools v00_01_01 )
find_ups_product( nusystematics v00_01_01 )
if(DEFINED ENV{CAFFE_LIB} )
  find_ups_product(caffe)
endif()
if(DEFINED ENV{LAPACK_LIB} )
  find_ups_product( lapack )
endif()

# macros for dictionary and simple_plugin
include(ArtDictionary)
include(ArtMake)
include(BuildPlugins)

# ADD SOURCE CODE SUBDIRECTORIES HERE
add_subdirectory(dune)
# release database
add_subdirectory(releaseDB)
# subdirectory for test code
add_subdirectory(test)
# ups - table and config files
add_subdirectory(ups)
# subdirectory for fcl files
add_subdirectory(fcl)

# packaging utility
include(UseCPack)
