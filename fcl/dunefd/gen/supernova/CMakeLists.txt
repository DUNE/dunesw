add_subdirectory(legacy)
add_subdirectory(flat)
add_subdirectory(livermore)
add_subdirectory(garching)
add_subdirectory(gkvm)

# Install fcl files in /job subdirectory.

install_fhicl()

# Also put a copy in the source tree.

FILE(GLOB fcl_files *.fcl)
install_source( EXTRAS ${fcl_files} )
