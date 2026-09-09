add_subdirectory(legacy)
# Install fcl files in /job subdirectory.

install_fhicl()

# Also put a copy in the source tree.

FILE(GLOB fcl_files *.fcl)
install_source( EXTRAS ${fcl_files} )

# Install Geant4 macro files alongside the FCLs.
FILE(GLOB mac_files *.mac)
install( FILES ${mac_files} DESTINATION ${dunesw_FHICL_DIR} )
