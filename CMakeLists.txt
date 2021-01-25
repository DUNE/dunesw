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

cmake_minimum_required (VERSION 3.12...3.18 FATAL_ERROR)

project(dunetpc LANGUAGES CXX)

# cetbuildtools contains our cmake modules
find_package(cetbuildtools REQUIRED)

list(APPEND CMAKE_MODULE_PATH $ENV{CANVAS_ROOT_IO_DIR}/Modules)

include(CetCMakeEnv)
cet_cmake_env()

set_install_root()

cet_set_compiler_flags(DIAGS CAUTIOUS
  WERROR
  NO_UNDEFINED
  EXTRA_FLAGS -pedantic -Wno-unused-local-typedefs
)
##add_definitions(-DGENIE_PRE_R3)

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
find_ups_product( nuevdb )
find_ups_product( nug4 )
find_ups_product( nugen )
find_ups_product( genie )
find_ups_product( nurandom )
find_ups_product( art v1_09_00 )
find_ups_product(art_root_io)
find_ups_product( clhep v2_1_3_0 )
find_ups_product( messagefacility v1_10_00 )
find_ups_product( postgresql v9_1_5 )
find_ups_product( dune_raw_data )
find_ups_product( dunepdsprce v0_0_3 )
find_ups_product( artdaq_core v01_03_6 )
find_ups_product( ifdh_art )
find_ups_product( ifdhc )
find_ups_geant4( )
find_ups_product( systematicstools v00_01_01 )
find_ups_product( nusystematics v00_01_01 )
if(DEFINED ENV{CAFFE_LIB} )
  find_ups_product(caffe)
endif()
if(DEFINED ENV{LAPACK_LIB} )
  find_ups_product( lapack )
endif()
if(( DEFINED ENV{TENSORFLOW_DIR} ) AND ( DEFINED ENV{TRTIS_CLIENTS_DIR} ))
  # find tensorflow library
  find_ups_product( protobuf )
  find_ups_product( tensorflow )
  find_ups_product( trtis_clients )
  find_ups_product( larrecodnn v1_00_00 )
  cet_find_library(TENSORFLOW NAMES tensorflow-core PATHS ENV TENSORFLOW_LIB NO_DEFAULT_PATH )
  cet_find_library(PROTOBUF NAMES protobuf PATHS ENV PROTOBUF_LIB NO_DEFAULT_PATH )
endif()
# artdaq_core Utility library
cet_find_library( ARTDAQ-CORE_UTILITIES NAMES artdaq-core_Utilities PATHS ENV ARTDAQ_CORE_LIB )

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
