add_subdirectory(legacy)
add_subdirectory(opdet)
add_subdirectory(systematic_variation)
add_subdirectory(wiremod)

# Install fcl files in /job subdirectory.

install_fhicl()

# Also put a copy in the source tree.

FILE(GLOB fcl_files *.fcl)
install_source( EXTRAS ${fcl_files} )
