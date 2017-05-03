# dunetpc/fc/common.CMakeLists.txt

# David Adams
# Aprtil 2017

# Common (i.e. multi-detector fcl configurations.

install_fhicl()

# Also put a copy in the source tree.
FILE(GLOB fcl_files *.fcl)
install_source( EXTRAS ${fcl_files} )

