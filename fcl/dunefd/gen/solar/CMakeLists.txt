add_subdirectory(alpha)
add_subdirectory(electron)
add_subdirectory(gamma)
add_subdirectory(marley)
add_subdirectory(neutron)
add_subdirectory(single)

# Install fcl files in /job subdirectory.
install_fhicl()

# Also put a copy in the source tree.

FILE(GLOB fcl_files *.fcl)
install_source( EXTRAS ${fcl_files} )