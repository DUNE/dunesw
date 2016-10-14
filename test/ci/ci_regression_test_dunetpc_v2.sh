#!/usr/bin/env bash


function usage {
      cat <<EOF
   usage: $0 [options]
      trigger build of ${proj_PREFIX}_ci continuous intergration build.
   options:
      --executable  Define the executable to run
      --nevents     Define the number of events to process
      --stage       Define the stage number used to parse the right testmask column number
      --fhicl       Set the FHiCl file to use to run the test
      --input       Set the file on which you want to run the test
      --outputs     Define a list of couple <output_stream>:<output_filename> using "," as separator
      --stage-name  Define the name of the test
      --testmask    Define the name of the testmask file
EOF
} 

function initialize
{
    TASKSTRING="initialize"
    trap 'LASTERR=$?; echo -e "\nCI MSG BEGIN\n `basename $0`: error at line ${LINENO}\n Stage: ${STAGE_NAME}\n Task: ${TASKSTRING}\n exit status: ${LASTERR}\nCI MSG END\n"; exit ${LASTERR}' ERR

    echo "initialize $@"

    #~~~~~~~~~~~~~~~ DEFAULT VALUES ~~~~~~~~~~~~~~~~
    EXECUTABLE_NAME=no_executable_defined
    NEVENTS=1
    TESTMASK="testmask.txt"
    INPUT_FILE=""
    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    #~~~~~~~~~~~~~~~~~~~~~~GET VALUE FROM THE CI_TESTS.CFG ARGS SECTION~~~~~~~~~~~~~~~
    while :
    do
      case "x$1" in
      x-h|x--help)   usage;                                                                         exit;;
      x--executable) EXECUTABLE_NAME="${2}";                                                        shift; shift;;
      x--nevents)    NEVENTS="${2}";                                                                shift; shift;;
      x--stage)      STAGE="${2}";                                                                   shift; shift;;
      x--fhicl)      FHiCL_FILE="${2}";                                                             shift; shift;;
      x--input)      INPUT_FILE="${2}";                                                             shift; shift;;
      x--outputs)    OUTPUT_LIST="${2}"; OUTPUT_STREAM="${OUTPUT_LIST//,/ -o }";                    shift; shift;;
      x--stage-name) STAGE_NAME="${2}";                                                              shift; shift;;
      x--testmask)   TESTMASK="${2}";                                                               shift; shift;;
      x)                                                                                            break;;
      x*)            echo "Unknown argument $1"; usage; exit 1;;
      esac
    done

    #~~~~~~~~~~~~~~~~~~~~~PARSE THE TESTMASK FILE TO UNDERSTAND WHICH FUNCTION TO RUN ~~~~~~~~~~~~
    check_data_production=$(sed -n '1p' ${TESTMASK} | cut -d ' ' -f ${STAGE})
    check_compare_names=$(sed -n '2p' ${TESTMASK} | cut -d ' ' -f ${STAGE})
    check_compare_size=$(sed -n '3p' ${TESTMASK} | cut -d ' ' -f ${STAGE})

    echo "Input file:  ${INPUT_FILE}"
    echo "Output files: ${OUTPUT_LIST}"
    echo "FHiCL file:  ${FHiCL_FILE}"
    echo
    echo -e "\nRunning\n `basename $0` $@"

    exitstatus $?
}


function data_production
{
    TASKSTRING="data_production"
    trap 'LASTERR=$?; echo -e "\nCI MSG BEGIN\n `basename $0`: error at line ${LINENO}\n Stage: ${STAGE_NAME}\n Task: ${TASKSTRING}\n exit status: ${LASTERR}\nCI MSG END\n"; exit ${LASTERR}' ERR

    #~~~~~~~~~~~~~IF THE TESTMASK VALUE IS SET TO 1 THEN RUN THE PRODUCTION OF THR DATA~~~~~~~~~~~~~~~~~~
    if [[ "${1}" -eq 1 ]]
    then

        echo -e "\nNumber of events for ${STAGE_NAME} stage: $NEVENTS\n"
        echo ${EXECUTABLE_NAME} --rethrow-all -n ${NEVENTS} -o ${OUTPUT_STREAM} --config ${FHiCL_FILE} ${INPUT_FILE}
        echo

        ${EXECUTABLE_NAME} --rethrow-all -n ${NEVENTS} -o ${OUTPUT_STREAM} --config ${FHiCL_FILE} ${INPUT_FILE}
    else
        echo -e "\nCI MSG BEGIN\n Stage: ${STAGE_NAME}\n Task: ${TASKSTRING}\n skipped\nCI MSG END\n"
    fi
    exitstatus $?
}

function generate_data_dump
{
    TASKSTRING="generate_data_dump for ${file_stream} output stream"

    trap 'LASTERR=$?; echo -e "\nCI MSG BEGIN\n `basename $0`: error at line ${LINENO}\n Stage: ${STAGE_NAME}\n Task: ${TASKSTRING}\n exit status: ${LASTERR}\nCI MSG END\n"; exit ${LASTERR}' ERR

    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PRINT THE COMMAND TO LOG AND THEN GENERATE THE DUMP FOR THE REFERENCE FILE ~~~~~~~~~~~~~~~~~~~
    echo -e "\nGenerating Dump for ${reference_file}"
    echo "${EXECUTABLE_NAME} --rethrow-all -n ${NEVENTS} --config eventdump.fcl ${reference_file} > ${reference_file//.root}.dump"

    ${EXECUTABLE_NAME} --rethrow-all -n ${NEVENTS} --config eventdump.fcl "${reference_file}" > "${reference_file//.root}".dump
    #~~~~~~~~~~~~~~~~~~~~~~~~~SAVE IN A VARIABLE THE PARSED REFERENCE DUMP FILE ~~~~~~~~~~~~~~~~~~~~~~
    OUTPUT_REFERENCE=$(cat "${reference_file//.root}".dump | sed -e  '/PROCESS NAME/,/^\s*$/!d ; s/PROCESS NAME.*$// ; /^\s*$/d' )

    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PRINT THE COMMAND TO LOG AND THEN GENERATE THE DUMP FOR THE CURRENT FILE ~~~~~~~~~~~~~~~~~~~
    echo -e "\nGenerating Dump for ${current_file}"
    echo "${EXECUTABLE_NAME} --rethrow-all -n ${NEVENTS} --config eventdump.fcl ${current_file} > ${current_file//.root}.dump"

    ${EXECUTABLE_NAME} --rethrow-all -n ${NEVENTS} --config eventdump.fcl "${current_file}" > "${current_file//.root}".dump
    #~~~~~~~~~~~~~~~~~~~~~~~~~SAVE IN A VARIABLE THE PARSED CURRENT DUMP FILE ~~~~~~~~~~~~~~~~~~~~~~
    OUTPUT_CURRENT=$(cat "${current_file//.root}".dump | sed -e  '/PROCESS NAME/,/^\s*$/!d ; s/PROCESS NAME.*$// ; /^\s*$/d' )

    echo -e "\nReference files for ${file_stream} output stream:"
    echo -e "\n${reference_file//.root}.dump\n"
    echo "$OUTPUT_REFERENCE"
    echo -e "\nCurrent files for ${file_stream} output strea:"
    echo -e "\n${current_file//.root}.dump\n"
    echo "$OUTPUT_CURRENT"

    exitstatus $?
}

function compare_products_names
{       
    TASKSTRING="compare_products_names for ${file_stream} output stream"

    if [[ "$1" -eq 1 ]]
    then 

        echo -e "\nCompare products names for ${file_stream} output stream."
        #~~~~~~~~~~~~~~~~CHECK IF THERE'S A DIFFERENCE BEETWEEN THE TWO DUMP FILES IN THE FIRST FOUR COLUMNS~~~~~~~~~~~~~~
        DIFF=$(diff  <(sed 's/\.//g ; /PROCESS NAME/,/^\s*$/!d ; s/PROCESS NAME.*$// ; /^\s*$/d' ${reference_file//.root/.dump} | cut -d "|" -f -4 ) <(sed 's/\.//g ; /PROCESS NAME/,/^\s*$/!d ; s/PROCESS NAME.*$// ; /^\s*$/d' ${current_file//.root/.dump} | cut -d "|" -f -4 ) )
        STATUS=$?

        echo -e "\nCheck for added/removed data products"
        echo -e "difference(s)\n"
        #~~~~~~~~~~~~~~~IF THERE'S A DIFFERENCE EXIT WITH ERROR CODE 200~~~~~~~~~~~~~~~
        if [[ "${STATUS}" -ne 0  ]]; then
            echo "${DIFF}"
            exitstatus 200
        else
            echo -e "none\n\n"
        fi
    else
        echo -e "\nCI MSG BEGIN\n Stage: ${STAGE_NAME}\n Task: ${TASKSTRING}\n skipped\nCI MSG END\n"
        exitstatus $?   
    fi
}

function compare_products_sizes
{
    TASKSTRING="compare_products_sizes for ${file_stream} output stream"

    if [[ "${1}" -eq 1 ]]
    then
        
        echo -e "\nCompare products sizes for ${file_stream} output stream.\n"
        #~~~~~~~~~~~~~~~~CHECK IF THERE'S A DIFFERENCE BEETWEEN THE TWO DUMP FILES,IN ALL THE COLUMNS~~~~~~~~~~~~~~
        DIFF=$(diff  <(sed 's/\.//g ; /PROCESS NAME/,/^\s*$/!d ; s/PROCESS NAME.*$// ; /^\s*$/d' ${reference_file//.root/.dump}) <(sed 's/\.//g ; /PROCESS NAME/,/^\s*$/!d ; s/PROCESS NAME.*$// ; /^\s*$/d' ${current_file//.root/.dump}) )
        STATUS=$?
        echo -e "\nCheck for differences in the size of data products"
        echo -e "difference(s)\n"

        #~~~~~~~~~~~~~~~IF THERE'S A DIFFERENCE EXIT WITH ERROR CODE 201 ~~~~~~~~~~~~~~~~~~~~~~~
        if [[ "${STATUS}" -ne 0 ]]; then
            echo "${DIFF}"
            exitstatus 201
        else
            echo -e "none\n\n"
        fi
    else
        echo -e "\nCI MSG BEGIN\n Stage: ${STAGE_NAME}\n Task: ${TASKSTRING}\n skipped\nCI MSG END\n"
        exitstatus $?
    fi
}

#~~~~~~~~~~~~~~~~~~~~~~~PRINT AN ERROR MESSAGE IN THE PROGRAM EXIT WITH AN ERROR CODE~~~~~~~~~~~~~~~~
function exitstatus
{
    EXITSTATUS="$1"
    echo -e "\nCI MSG BEGIN\n Stage: ${STAGE_NAME}\n Task: ${TASKSTRING}\n exit status: ${EXITSTATUS}\nCI MSG END\n"
    if [[ "${EXITSTATUS}" -ne 0 ]]; then
      exit "${EXITSTATUS}"
    fi
}



#~~~~~~~~~~~~~~~~~~~~~~~~MAIN OF THE SCRIPT~~~~~~~~~~~~~~~~~~
trap 'LASTERR=$?; echo -e "\nCI MSG BEGIN\n `basename $0`: error at line ${LINENO}\n Stage: ${STAGE_NAME}\n Task: ${TASKSTRING}\n exit status: ${LASTERR}\nCI MSG END\n"; exit ${LASTERR}' ERR

initialize $@

data_production "${check_data_production}"

IFS=$','

#~~~~~~~~~~~~~~~~PROCESS ALL THE FILES DECLARED INTO THE OUTPUT LIST~~~~~~~~~~~~~~~~~
for filename in ${OUTPUT_LIST}
do
    file_stream=$(echo "${filename}" | cut -d ':' -f 1)
    current_file=$(echo "${filename}" | cut -d ':' -f 2)
    reference_file="${current_file//Current/Reference}"

    if [[ "${check_compare_names}" -eq 1  || "${check_compare_size}" -eq 1 ]]
    then
        generate_data_dump
    else
        break
    fi

    compare_products_names "${check_compare_names}"

    compare_products_sizes "${check_compare_size}"
done
unset IFS
