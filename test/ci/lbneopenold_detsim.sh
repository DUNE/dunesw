#!/bin/bash
# echurch@fnal.gov

#get-cert -i
#voms-proxy-init -noregen -rfc -voms lbne:/lbne/Role=Analysis

cp  ${LBNECODE_DIR}/job/prodsingle_lbne35t.fcl .
#echo "services.user.FileCatalogMetadataExtras.RenameTemplate: '' " >> ./standard_detsim_lbne.fc
echo "outputs.out1.fileName: 'openclose_detsim_lbne.root'" >> ./prodsingle_lbne35t.fcl
echo "source.module_type: RootInput" >> ./prodsingle_lbne35t.fcl
echo "source.maxEvents: -1" >> ./prodsingle_lbne35t.fcl

# We want to just run detsim in this job
sed -e '/generator/s/^/#/g' -i prodsingle_lbne35t.fcl 
sed -e '/largeant/s/^/#/g'  -i prodsingle_lbne35t.fcl 
sed -i '/simulate\: /asimulate\: [ daq, rns ]' -i prodsingle_lbne35t.fcl

lar --process-name citest-detsim -c prodsingle_lbne35t.fcl -s $1 -n 1 -o openclose_detsim_lbne.root -T openclose_detsim_hist_lbne.root
