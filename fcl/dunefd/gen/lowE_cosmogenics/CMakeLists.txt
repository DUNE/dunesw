install_fhicl()

# The sampling table and helper scripts are installed alongside the FCLs so the
# generators work from an installed release. The 13 MB source CSV the table is
# reduced from is deliberately not in this repository -- see README.md.
# The table is .dat, not .txt: the top-level .gitignore excludes *.txt, which
# would silently drop it from the repository and install an empty glob.
FILE(GLOB lowE_cosmogenics_extras *.dat *.py *.md)
install( FILES ${lowE_cosmogenics_extras} DESTINATION ${dunesw_FHICL_DIR} )
