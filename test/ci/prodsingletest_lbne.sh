#!/bin/bash
#Test LArSoft code with "prodsingle.fcl".


cp  ${LBNECODE_DIR}/job/prodsingle_lbne35t.fcl .
strace -o lar.strace lar -c ${LBNECODE_DIR}/job/prodsingle_lbne35t.fcl -n 1 -o single_lbne_gen.root -T single_lbne_hist.root
