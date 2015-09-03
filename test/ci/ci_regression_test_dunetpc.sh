#!/bin/bash

NEVENTS=$1
STEP=$2
LARSOFT_REFERENCE_VERSION=$3

declare -a PREVSTEPS=("" "gen" "geant" "detsim" "reco")
declare -a STEPS=("gen" "geant" "detsim" "reco" "ana")

REFERENCE_FILE="AntiMuonCutEvents_LSU_v2_dune35t_Reference_${PREVSTEPS[STEP]}_${LARSOFT_REFERENCE_VERSION}.root"
if [ $STEP -eq 0 ]; then REFERENCE_FILE=""; fi


function larsoft_data_production
{

    echo -e "\nNumber of events for ${STEPS[STEP]} step: $NEVENTS\n"

    lar --rethrow-default -n $NEVENTS -o AntiMuonCutEvents_LSU_v2_dune35t_Current_${STEPS[STEP]}.root --config ci_test_${STEPS[STEP]}_dunetpc.fcl ${REFERENCE_FILE}

}

function compare_data_products
{

    echo -e "\nCompare data products."
    echo    "Reference files for ${STEPS[STEP]} step generated using LARSOFT_VERSION $LARSOFT_REFERENCE_VERSION"
    echo -e "Current files for ${STEPS[STEP]} step generated using LARSOFT_VERSION $LARSOFT_VERSION\n"

    lar --rethrow-default -n $NEVENTS --config eventdump.fcl AntiMuonCutEvents_LSU_v2_dune35t_Current_${STEPS[STEP]}.root > AntiMuonCutEvents_LSU_v2_dune35t_Current_${STEPS[STEP]}.dump

    lar --rethrow-default -n $NEVENTS --config eventdump.fcl AntiMuonCutEvents_LSU_v2_dune35t_Reference_${STEPS[STEP]}_${LARSOFT_REFERENCE_VERSION}.root > AntiMuonCutEvents_LSU_v2_dune35t_Reference_${STEPS[STEP]}.dump

    echo -e "\nAntiMuonCutEvents_LSU_v2_dune35t_Current_${STEPS[STEP]}.dump\n"

    OUTPUT_CURRENT=$(cat AntiMuonCutEvents_LSU_v2_dune35t_Current_${STEPS[STEP]}.dump | sed -e  '/PROCESS NAME/,/^\s*$/!d ; s/PROCESS NAME.*$// ; /^\s*$/d' ); echo "$OUTPUT_CURRENT"

    echo -e "\nAntiMuonCutEvents_LSU_v2_dune35t_Reference_${STEPS[STEP]}.dump\n"

    OUTPUT_REFERENCE=$(cat AntiMuonCutEvents_LSU_v2_dune35t_Reference_${STEPS[STEP]}.dump | sed -e  '/PROCESS NAME/,/^\s*$/!d ; s/PROCESS NAME.*$// ; /^\s*$/d' ); echo "$OUTPUT_REFERENCE"

    DIFF=$(diff  <(echo "$OUTPUT_CURRENT" | awk '{$NF=""}1' ) <(echo "$OUTPUT_REFERENCE" | awk '{$NF=""}1' ) )

    echo -e "\ndifference(s)\n"

    echo "$DIFF"

    if [ ${#DIFF} -gt 0 ]; then
       exit 1;
    fi
}

trap 'LASTERR=$?; echo `basename $0`: line ${LINENO}: exit status: ${LASTERR}; exit ${LASTERR}' ERR

echo -e "\nRun `basename $0` script"

larsoft_data_production

compare_data_products
