#!/bin/bash

function initialize
{
    trap 'LASTERR=$?; echo -e "\nCI MSG BEGIN\n `basename $0`: error at line ${LINENO}\n Stage: ${STAGE}\n Task: ${TASKSTRING}\n exit status: ${LASTERR}\nCI MSG END\n"; exit ${LASTERR}' ERR

    echo "initialize $@"

    NEVENTS=$1
    STAGE=$2
    STEP=$3
    LARSOFT_REFERENCE_VERSION=$4
    EXPCODE=$5
    OUTPUT_FILE=$6
    INPUT_FILE=$7

    #INPUT_FILE="${BASEFILENAME}_Reference_${STAGE}_${LARSOFT_REFERENCE_VERSION}.root"
    #OUTPUT_FILE="${BASEFILENAME}_Current_${STAGE}.root"

    FHiCL_FILE="ci_test_${STAGE}_${EXPCODE}.fcl"

    echo "Input file:  $INPUT_FILE"
    echo "Output file: $OUTPUT_FILE"
    echo "FHiCL file:  $FHiCL_FILE"
    echo
    echo -e "\nRunning\n `basename $0` $@"

}


function larsoft_data_production
{

    trap 'LASTERR=$?; echo -e "\nCI MSG BEGIN\n `basename $0`: error at line ${LINENO}\n Stage: ${STAGE}\n Task: ${TASKSTRING}\n exit status: ${LASTERR}\nCI MSG END\n"; exit ${LASTERR}' ERR

    echo -e "\nNumber of events for ${STAGE} step: $NEVENTS\n"
    echo lar --rethrow-all -n ${NEVENTS} -o ${OUTPUT_FILE} --config ${FHiCL_FILE} ${INPUT_FILE}
    echo

    lar --rethrow-all -n $NEVENTS -o $OUTPUT_FILE --config $FHiCL_FILE ${INPUT_FILE}

}

function compare_data_products
{
    trap 'LASTERR=$?; echo -e "\nCI MSG BEGIN\n `basename $0`: error at line ${LINENO}\n Stage: ${STAGE}\n Task: ${TASKSTRING}\n exit status: ${LASTERR}\nCI MSG END\n"; exit ${LASTERR}' ERR

    declare -a CHECKMSG=("Check for added/removed data products" "Check for differences in the size of data products")


    if [ ${COMPAREINIT} -eq 0 ]; then

        echo lar --rethrow-all -n $NEVENTS --config eventdump.fcl ${OUTPUT_FILE}

        lar --rethrow-all -n $NEVENTS --config eventdump.fcl ${OUTPUT_FILE} > ${OUTPUT_FILE//.root/.dump}
        OUTPUT_CURRENT=$(cat ${OUTPUT_FILE//.root/.dump} | sed -e  '/PROCESS NAME/,/^\s*$/!d ; s/PROCESS NAME.*$// ; /^\s*$/d' )



        REFERENCE_FILE=${OUTPUT_FILE//Current/Reference}
        REFERENCE_FILE=${REFERENCE_FILE//.root/_${LARSOFT_REFERENCE_VERSION}.root}

        echo lar --rethrow-all -n $NEVENTS --config eventdump.fcl ${REFERENCE_FILE}

        lar --rethrow-all -n $NEVENTS --config eventdump.fcl ${REFERENCE_FILE} > ${REFERENCE_FILE//.root/.dump}
        OUTPUT_REFERENCE=$(cat ${OUTPUT_FILE//.root/.dump} | sed -e  '/PROCESS NAME/,/^\s*$/!d ; s/PROCESS NAME.*$// ; /^\s*$/d' )

        echo -e "\nCompare data products."
        echo    "Reference files for ${STAGE} stage generated using LARSOFT_VERSION $LARSOFT_REFERENCE_VERSION"
        echo -e "Current files for ${STAGE} stage generated using LARSOFT_VERSION $LARSOFT_VERSION\n"
        echo -e "\n${INPUT_FILE//.root/.dump}\n"
        echo "$OUTPUT_REFERENCE"
        echo -e "\n${OUTPUT_FILE//.root/.dump}\n"
        echo "$OUTPUT_CURRENT"
    fi

    trap - ERR

    DIFF=$(diff  <(echo "${OUTPUT_REFERENCE}" | cut -d "|" -f -$((4+$1)) | sed 's/\.//g' ) <(echo "${OUTPUT_CURRENT}" | cut -d "|" -f -$((4+$1)) | sed 's/\.//g' ) )

    trap 'LASTERR=$?; echo -e "\nCI MSG BEGIN\n `basename $0`: error at line ${LINENO}\n Stage: ${STAGE}\n Task: ${TASKSTRING}\n exit status: ${LASTERR}\nCI MSG END\n"; exit ${LASTERR}' ERR

    echo
    echo ${CHECKMSG[$1]}
    echo "difference(s)"
    echo

    if [ ${#DIFF} -gt 0 ]; then
       echo "${DIFF}"
       exitstatus $((2000+$1)) "$FUNCNAME step $1";
    else
       echo -e "none\n\n"
    fi

    COMPAREINIT=1

}

function exitstatus
{
    EXITSTATUS=$1

    echo -e "\nCI MSG BEGIN\n Stage: ${STAGE}\n Task: ${TASKSTRING}\n exit status: ${EXITSTATUS}\nCI MSG END\n"
    if [ ${EXITSTATUS} -ne 0 ]; then
      exit ${EXITSTATUS}
    fi
}

trap 'LASTERR=$?; echo -e "\nCI MSG BEGIN\n `basename $0`: error at line ${LINENO}\n Stage: ${STAGE}\n Task: ${TASKSTRING}\n exit status: ${LASTERR}\nCI MSG END\n"; exit ${LASTERR}' ERR

TASKSTRING="initialize"
initialize $@

exitstatus $?

if [ $(sed -n '1p' testmask_seq.txt | cut -d ' ' -f ${STEP}) -eq 1 ]; then
    TASKSTRING="larsoft_data_production"
    larsoft_data_production

    exitstatus $?
else
    TASKSTRING="larsoft_data_production"
    echo -e "\nCI MSG BEGIN\n Stage: ${STAGE}\n Task: ${TASKSTRING}\n skipped\nCI MSG END\n"
fi

COMPAREINIT=0

if [ $(sed -n '2p' testmask_seq.txt | cut -d ' ' -f ${STEP}) -eq 1 ]; then
    TASKSTRING="compare_data_products 0"
    compare_data_products 0 #Check for added/removed data products

    exitstatus $?
else
    TASKSTRING="compare_data_products 0"
    echo -e "\nCI MSG BEGIN\n Stage: ${STAGE}\n Task: ${TASKSTRING}\n skipped\nCI MSG END\n"
fi

if [ $(sed -n '3p' testmask_seq.txt | cut -d ' ' -f ${STEP}) -eq 1 ]; then
    TASKSTRING="compare_data_products 1"
    compare_data_products 1 #Check for differences in the size of data products

    exitstatus $?
else
    TASKSTRING="compare_data_products 1"
    echo -e "\nCI MSG BEGIN\n Stage: ${STAGE}\n Task: ${TASKSTRING}\n skipped\nCI MSG END\n"
fi
