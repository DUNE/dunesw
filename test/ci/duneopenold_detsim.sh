#!/bin/bash
# echurch@fnal.gov

#get-cert -i
#voms-proxy-init -noregen -rfc -voms dune:/dune/Role=Analysis

cp  ${DUNETPC_DIR}/job/prodsingle_dune35t.fcl .
#echo "services.user.FileCatalogMetadataExtras.RenameTemplate: '' " >> ./standard_detsim_dune.fc
echo "outputs.out1.fileName: 'openclose_detsim_dune.root'" >> ./prodsingle_dune35t.fcl
echo "source.module_type: RootInput" >> ./prodsingle_dune35t.fcl
echo "source.maxEvents: -1" >> ./prodsingle_dune35t.fcl
echo "services.user.TimeService.TriggerOffsetTPC: -1600" >> ./prodsingle_dune35t.fcl # for consistency with the (probably inadvertently set) parameter in file at /pnfs/dune/mc/dune/simulated/002/singleparticle_antimu_20141105_Simulation009.root that this test reads

# We want to just run detsim in this job
ed prodsingle_dune35t.fcl <<EOF
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

lar --process-name citest-detsim -c prodsingle_dune35t.fcl -s $1 -n 1 -o openclose_detsim_dune.root -T openclose_detsim_hist_dune.root
