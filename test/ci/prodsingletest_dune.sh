#!/bin/bash
#Test LArSoft code with "prodsingle.fcl".

# only try to strace if we have it..
strace() {
   if [ -x /usr/bin/strace ]
   then
       /usr/bin/strace "$@"
   else
       if [ "$1" = "-o" ]
       then
           shift
           shift
       fi
       "$@"
   fi
}

cp  ${DUNETPC_DIR}/job/prodsingle_dune35t.fcl .
strace -o lar.strace lar -c ${DUNETPC_DIR}/job/prodsingle_dune35t.fcl -n 1 -o single_dune_gen.root -T single_dune_hist.root
