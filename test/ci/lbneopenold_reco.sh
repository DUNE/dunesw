#!/bin/bash
# echurch@fnal.gov

cp  ${LBNECODE_DIR}/job/standard_reco_lbne.fcl .
#echo "services.user.FileCatalogMetadataExtras.RenameTemplate: '' " >> ./standard_reco_lbne_2D.fcl
echo "outputs.out1.fileName: 'openclose_reco2D_lbne.root'" >> ./standard_reco_lbne.fcl
lar --process-name citest-reco2D -c standard_reco_lbne_2D.fcl -s ../lar_ci_openold_detsim_lbnecode/openclose_detsim_lbne.root -n 1 -o openclose_reco_lbne.root -T openclose_reco_hist_lbne.root
