#!/bin/bash
#
# DUNE geometry tests.
# Usage:
#
# testgeo.sh [Geometry ...]
# 
# Default geometries defined in DEFAULT_GEOMETRIES below.
#
# Copied from larcore/Geometry/test/testgeo.csh .
#

DEFAULT_GEOMETRIES=( 'dunefd' 'dune35t' )
INCLUDE_FILES=( 'geometry_dune.fcl' )


################################################################################
function TestGeometry() {
	local Geometry="$1"
	
	echo "Testing geometry for ${Geometry}"
	
	local ConfigFile="test_${Geometry}_geometry.fcl"
	
	# preamble and prologue
	cat <<-EOC > "$ConfigFile"
	#
	# Test for ${Geometry} geometry
	#
	BEGIN_PROLOG
	# this item will be included by geotest.fcl: we need a temporary fake one
	detector_geo: {}
	END_PROLOG
	
	EOC
	
	# add include files as needed
	local IncludeFile
	for IncludeFile in "${INCLUDE_FILES[@]}" ; do
		echo "#include \"${IncludeFile}\"" >> "$ConfigFile"
	done
	
	# overriding the original template file
	cat <<-EOC >> "$ConfigFile"
	
	# geotest.fcl is provided by larcore (larcore/Geometry/test)
	#include "geotest.fcl"
	
	services.user.Geometry:               @local::${Geometry}_geo
	services.user.ExptGeoHelperInterface: @local::dune_geometry_helper
	EOC
	
	local LogFile="${ConfigFile%.fcl}.log"
	local res
	lar -c "$ConfigFile" 2>&1 | tee "$LogFile"
	res=${PIPESTATUS[0]}
	
	echo "Test completed with exit code ${res}, log file: ${LogFile}"
	if [[ $res == 0 ]]; then
		rm -f "$ConfigFile" *.root
	fi
	
	return "$res"
} # TestGeometry()


################################################################################
declare -a Geometries
if [[ $# -gt 0 ]]; then
	Geometries=( "$@" )
else
	Geometries=( "${DEFAULT_GEOMETRIES[@]}" )
fi

declare -i nTests=0 nErrors=0
for Geometry in "${Geometries[@]}" ; do
	let ++nTests
	TestGeometry "$Geometry"
	res=$?
	[[ $res != 0 ]] && let ++nErrors
done

if [[ $nErrors == 0 ]]; then
	echo "All ${nTests} tests successfully completed."
else
	echo "${nErrors} tests out of ${nTests} failed."
fi
exit $nErrors
