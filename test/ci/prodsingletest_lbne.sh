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

cp  ${LBNECODE_DIR}/job/prodsingle_lbne35t.fcl .
strace -o lar.strace lar -c ${LBNECODE_DIR}/job/prodsingle_lbne35t.fcl -n 1 -o single_lbne_gen.root -T single_lbne_hist.root
