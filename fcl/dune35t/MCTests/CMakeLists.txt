# Install fcl files in /job subdirectory.
add_subdirectory(DataOverlay)

install_fhicl()

# Also put a copy in the source tree.

FILE(GLOB fcl_files *.fcl)
install_source( EXTRAS ${fcl_files} )
