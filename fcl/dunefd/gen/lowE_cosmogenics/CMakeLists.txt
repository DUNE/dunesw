install_fhicl()

# Install the sampling table and helper scripts alongside the FCLs.
# (The table is .dat because the top-level .gitignore excludes *.txt.)
FILE(GLOB lowE_cosmogenics_extras *.dat *.py *.md)
install( FILES ${lowE_cosmogenics_extras} DESTINATION ${dunesw_FHICL_DIR} )
