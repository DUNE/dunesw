# ======================================================================
#  dunesw main build file
# ======================================================================


# use cmake 3.14 or later
cmake_minimum_required (VERSION 3.19 FATAL_ERROR)

project(dunesw VERSION 09.41.00.02 LANGUAGES CXX)

# cetbuildtools contains our cmake modules
find_package(cetbuildtools REQUIRED)

include(CetCMakeEnv)
cet_cmake_env()

cet_set_compiler_flags(DIAGS CAUTIOUS
  WERROR
  NO_UNDEFINED
  EXTRA_FLAGS -pedantic -Wno-unused-local-typedefs
)
find_ups_product( art )
find_ups_product( art_root_io )
find_ups_product( canvas_root_io )
find_ups_boost( )
find_ups_root()
find_ups_product( cetbuildtools )
find_ups_product( dunecore )
find_ups_product( larcore )
find_ups_product( lardata )
find_ups_product( larcorealg )
find_ups_product( lardataalg )

cet_report_compiler_flags()

# macros for artdaq_dictionary and simple_plugin
include(ArtDictionary)
include(ArtMake)
include(BuildPlugins)

# nothing yet

#add_subdirectory(dunesw)
add_subdirectory(ups)
add_subdirectory(fcl)
add_subdirectory(test)

include(UseCPack)
