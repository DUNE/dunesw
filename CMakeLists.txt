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

cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(dunetpc VERSION 09.28.02.01 LANGUAGES CXX)

# cetbuildtools contains our cmake modules
find_package(cetbuildtools REQUIRED)

# Make target names shorter (dune::X vs dunetpc::dune_X).
set(dunetpc_NAMESPACE dune)

include(CetCMakeEnv)
cet_cmake_env()

# Find our own CMake modules, and tell everyone else where to find them.
cet_cmake_module_directories(Modules BINARY)

set_install_root()

cet_set_compiler_flags(DIAGS CAUTIOUS
  WERROR
  NO_UNDEFINED
  EXTRA_FLAGS -pedantic -Wno-unused-local-typedefs
)
##add_definitions(-DGENIE_PRE_R3)

cet_report_compiler_flags()

# these are minimum required versions, not the actual product versions
find_ups_boost( ) # Needs to be first to cover for a missing transitive
                  # dependency from artdaq_core.
find_ups_geant4( )
find_ups_root( )

find_ups_product( eigen )
include_directories( $ENV{EIGEN_INC} )

find_ups_product( art v3_09_00 )
find_ups_product( art_root_io )
find_ups_product( artdaq_core v01_03_6 )
find_ups_product( canvas )
find_ups_product( canvas_root_io )
find_ups_product( cetlib_except )
find_ups_product( cetlib )
find_ups_product( clhep v2_1_3_0 )
find_ups_product( dune_raw_data )
find_ups_product( dunepdsprce v0_0_3 )
find_ups_product( fhiclcpp )
find_ups_product( genie )
find_ups_product( hep_concurrency )
find_ups_product( ifdh_art )
find_ups_product( ifdhc )
find_ups_product( larana )
find_ups_product( larcore )
find_ups_product( larcorealg )
find_ups_product( larcoreobj )
find_ups_product( lardata )
find_ups_product( lardataalg )
find_ups_product( lardataobj )
find_ups_product( larevt )
find_ups_product( larpandora )
find_ups_product( larreco )
find_ups_product( larsim )
find_ups_product( messagefacility v1_10_00 )
find_ups_product( nuevdb )
find_ups_product( nug4 )
find_ups_product( nugen )
find_ups_product( nurandom )
find_ups_product( nusimdata )
find_ups_product( nusystematics  )
find_ups_product( nutools )
find_ups_product( pandora )
find_ups_product( postgresql v9_1_5 )
find_ups_product( systematicstools  )
find_ups_product( fftw )
if(DEFINED ENV{LAPACK_LIB} )
  find_ups_product( lapack )
endif()
if(( DEFINED ENV{TENSORFLOW_DIR} ) AND ( DEFINED ENV{TRITON_DIR} ))
  # find tensorflow library
  find_ups_product( protobuf )
  find_ups_product( tensorflow )
  find_ups_product( triton )
  find_ups_product( larrecodnn )
  cet_find_library(TENSORFLOW_CC NAMES tensorflow_cc PATHS ENV TENSORFLOW_LIB NO_DEFAULT_PATH )
  cet_find_library(TENSORFLOW_FRAMEWORK NAMES tensorflow_framework PATHS ENV TENSORFLOW_LIB NO_DEFAULT_PATH )
  set(TENSORFLOW ${TENSORFLOW_CC} ${TENSORFLOW_FRAMEWORK})
  cet_find_library(PROTOBUF NAMES protobuf PATHS ENV PROTOBUF_LIB NO_DEFAULT_PATH )
endif()
# artdaq_core Utility library
cet_find_library( ARTDAQ-CORE_UTILITIES NAMES artdaq-core_Utilities PATHS ENV ARTDAQ_CORE_LIB )


# Define an export set for tool support to enable simpler per-tool build
# call.
cet_register_export_set(SET_NAME PluginTypes NAMESPACE art_plugin_types)

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
# CMake Modules
add_subdirectory(Modules)
# ups - table and config files
add_subdirectory(ups)
# subdirectory for fcl files
add_subdirectory(fcl)

# packaging utility
include(UseCPack)
