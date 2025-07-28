#!/bin/bash

export _condor_CREDD_HOST
export _condor_COLLECTOR_HOST
for _condor_COLLECTOR_HOST in gpcollector04.fnal.gov
do
    slist=`condor_status -schedd -af name -constraint IsJobsubLite`
    for _condor_CREDD_HOST in $slist
    do
        echo "updating credmon on $_condor_CREDD_HOST"
        /usr/bin/condor_vault_storer dune
    done
done
