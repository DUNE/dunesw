#!/bin/bash
#Test LArSoft code with "prodsingle.fcl".


cp  ${LBNECODE_DIR}/job/prodsingle_lbne35t.fcl .
strace -o lar.strace lar -c ${LBNECODE_DIR}/job/prodsingle_lbne35t.fcl -n 1 -o single_gen.root -T single_hist.root
