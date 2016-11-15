#!/bin/bash

################################################################################
################################################################################
################################################################################
#####                                                                      #####
#####  THIS SCRIPT IS JUST AN EXAMPLE. RE-WRITE IT FOR YOUR OWN PURPOSES.  #####
#####                                                                      #####
################################################################################
################################################################################
################################################################################



comm0="kx509;voms-proxy-init -noregen -rfc -voms dune:/dune/Role=Analysis;"

while true; do
    read -p "Do you wish to get a new grid proxy?" yn
    case $yn in
        [Yy]* ) eval $comm0;break;;
        [Nn]* ) echo "Continuing without creating new proxy";break;;
        * ) echo "Please answer yes or no.";;
    esac
done

#########################################################################

RUNNUMBERS=/dune/app/users/mthiesse/PersistentFiles/FullRunSelection.txt
DEFNAME="goodruns_35ton_sliced_$USER"

comm="samweb -e dune -v create-definition $DEFNAME \"("

while read run;
do
    comm=$comm"run_number $run or "
done < $RUNNUMBERS

comm2=${comm%????}
comm3=$comm2") and version v05_14_00 and data_tier sliced\""

while true; do
    read -p "Do you wish to (re)create definition named ${DEFNAME}?" yn
    case $yn in
        [Yy]* ) eval $comm3; break;;
        [Nn]* ) echo "Continuing without creating definition";break;;
        * ) echo "Please answer yes or no.";;
    esac
done


###########################################################################


DATETIME=$(date +"%Y-%m-%d_%H-%M-%S")
PROJECTNAME=${USER}_${DEFNAME}_${DATETIME}

comm4="samweb -e dune -v start-project --defname=$DEFNAME $PROJECTNAME"

while true; do
    read -p "Do you wish to create new SAM project with name ${PROJECTNAME} ?" yn
    case $yn in
[Yy]* ) eval $comm4; break;;
        [Nn]* ) echo "Continuing without creating project";break;;
	* ) echo "Please answer yes or no.";;
    esac
done
