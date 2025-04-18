# ======================================================================
#  dunesw main build file
# ======================================================================


# use cmake 3.14 or later
cmake_minimum_required (VERSION 3.20 FATAL_ERROR)
# cmake_policy(VERSION 3.19)

find_package(cetmodules REQUIRED)
project(dunesw LANGUAGES CXX)
set(${PROJECT_NAME}_CMAKE_PROJECT_VERSION_STRING 10.05.00d00)

include(CetCMakeEnv)
cet_cmake_env()

cet_set_compiler_flags(DIAGS CAUTIOUS
  WERROR
  NO_UNDEFINED
  EXTRA_FLAGS -pedantic -Wno-unused-local-typedefs
)

find_package( art REQUIRED EXPORT )
find_package( art_root_io REQUIRED EXPORT )
find_package( canvas_root_io REQUIRED EXPORT )
find_package( Boost REQUIRED )
find_package(ROOT REQUIRED)
find_package( dunecore REQUIRED EXPORT )
find_package( larcore REQUIRED EXPORT )
find_package( lardata REQUIRED EXPORT )
find_package( larcorealg REQUIRED EXPORT )
find_package( lardataalg REQUIRED EXPORT )
find_package( nurandom REQUIRED EXPORT )

cet_report_compiler_flags()

# macros for artdaq_dictionary and simple_plugin
include(ArtDictionary)
include(ArtMake)
include(BuildPlugins)

# nothing yet

#add_subdirectory(dunesw)
add_subdirectory(fcl)
add_subdirectory(test)

cet_cmake_config()
