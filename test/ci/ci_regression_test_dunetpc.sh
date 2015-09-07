#!/bin/bash

NEVENTS=$1
STEP=$2
LARSOFT_REFERENCE_VERSION=$3
BASEFILENAME="AntiMuonCutEvents_LSU_v2_dune35t"
EXPCODE="dunetpc"

declare -a STEPS=("" "gen" "geant" "detsim" "reco" "ana")

REFERENCE_FILE="${BASEFILENAME}_Reference_${STEPS[STEP]}_${LARSOFT_REFERENCE_VERSION}.root"
if [ $STEP -eq 0 ]; then REFERENCE_FILE=""; fi


function larsoft_data_production
{

    echo -e "\nNumber of events for ${STEPS[STEP+1]} step: $NEVENTS\n"

    lar --rethrow-default -n $NEVENTS -o ${BASEFILENAME}_Current_${STEPS[STEP+1]}.root --config ci_test_${STEPS[STEP+1]}_${EXPCODE}.fcl ${REFERENCE_FILE}

}

function compare_data_products
{

    declare -a CHECKMSG=("Check for added/removed data products" "Check for differences in the size of data products")


    if [ $COMPAREINIT -eq 0 ]; then

        lar --rethrow-default -n $NEVENTS --config eventdump.fcl ${BASEFILENAME}_Reference_${STEPS[STEP+1]}_${LARSOFT_REFERENCE_VERSION}.root > ${BASEFILENAME}_Reference_${STEPS[STEP+1]}.dump
        OUTPUT_REFERENCE=$(cat ${BASEFILENAME}_Reference_${STEPS[STEP+1]}.dump | sed -e  '/PROCESS NAME/,/^\s*$/!d ; s/PROCESS NAME.*$// ; /^\s*$/d' )

        lar --rethrow-default -n $NEVENTS --config eventdump.fcl ${BASEFILENAME}_Current_${STEPS[STEP+1]}.root > ${BASEFILENAME}_Current_${STEPS[STEP+1]}.dump
        OUTPUT_CURRENT=$(cat ${BASEFILENAME}_Current_${STEPS[STEP+1]}.dump | sed -e  '/PROCESS NAME/,/^\s*$/!d ; s/PROCESS NAME.*$// ; /^\s*$/d' )

        echo -e "\nCompare data products."
        echo    "Reference files for ${STEPS[STEP+1]} step generated using LARSOFT_VERSION $LARSOFT_REFERENCE_VERSION"
        echo -e "Current files for ${STEPS[STEP+1]} step generated using LARSOFT_VERSION $LARSOFT_VERSION\n"
        echo -e "\n${BASEFILENAME}_Reference_${STEPS[STEP+1]}.dump\n"
        echo "$OUTPUT_REFERENCE"
        echo -e "\n${BASEFILENAME}_Current_${STEPS[STEP+1]}.dump\n"
        echo "$OUTPUT_CURRENT"
    fi


    DIFF=$(diff  <(echo "$OUTPUT_REFERENCE" | awk -v MYNF=$((1-$1)) 'NF{NF-=MYNF}1' ) <(echo "$OUTPUT_CURRENT" | awk -v MYNF=$((1-$1)) 'NF{NF-=MYNF}1' ) )

    echo
    echo ${CHECKMSG[$1]}
    echo "difference(s)"
    echo

    if [ ${#DIFF} -gt 0 ]; then
       echo "$DIFF"
       exit 1;
    else
       echo -e "none\n\n"
    fi

    COMPAREINIT=1

}

trap 'LASTERR=$?; echo `basename $0`: line ${LINENO}: exit status: ${LASTERR}; exit ${LASTERR}' ERR

echo -e "\nRun `basename $0` script"

larsoft_data_production

COMPAREINIT=0
compare_data_products 0 #Check for added/removed data products

# compare_data_products 1 #Check for differences in the size of data products
