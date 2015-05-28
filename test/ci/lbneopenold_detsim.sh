#!/bin/bash
# echurch@fnal.gov

#get-cert -i
#voms-proxy-init -noregen -rfc -voms lbne:/lbne/Role=Analysis

cp  ${LBNECODE_DIR}/job/prodsingle_lbne35t.fcl .
#echo "services.user.FileCatalogMetadataExtras.RenameTemplate: '' " >> ./standard_detsim_lbne.fc
echo "outputs.out1.fileName: 'openclose_detsim_lbne.root'" >> ./prodsingle_lbne35t.fcl
echo "source.module_type: RootInput" >> ./prodsingle_lbne35t.fcl
echo "source.maxEvents: -1" >> ./prodsingle_lbne35t.fcl
echo "services.user.TimeService.TriggerOffsetTPC: -1600" >> ./prodsingle_lbne35t.fcl # for consistency with the (probably inadvertently set) parameter in file at /pnfs/lbne/mc/lbne/simulated/002/singleparticle_antimu_20141105_Simulation009.root that this test reads

# We want to just run detsim in this job
ed prodsingle_lbne35t.fcl <<EOF
g/generator/s/^/#/
g/largeant/s/^/#/
/simulate: /
a
simulate: [daq, rns ]
.
/RandomNumberGenerator/
a
  RandomNumberGenerator: {} # added back
.
w
q
EOF

lar --process-name citest-detsim -c prodsingle_lbne35t.fcl -s $1 -n 1 -o openclose_detsim_lbne.root -T openclose_detsim_hist_lbne.root
