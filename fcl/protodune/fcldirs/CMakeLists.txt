# Following dumps all cmake variables.
#message("======================================")
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach() 
#message("======================================")

# Install all fcl files in rundata in the rundata directory of the product fcl area.
install(
  DIRECTORY rundata
  DESTINATION ${dunesw_FHICL_DIR}
  FILES_MATCHING PATTERN *.fcl
)
install(
  DIRECTORY calib
  DESTINATION ${dunesw_FHICL_DIR}
  FILES_MATCHING PATTERN *.fcl
)
install(
  DIRECTORY pedestal
  DESTINATION ${dunesw_FHICL_DIR}
  FILES_MATCHING PATTERN *.fcl
)
