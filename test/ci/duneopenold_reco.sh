#!/bin/bash
# echurch@fnal.gov

cp  ${DUNETPC_DIR}/job/minimal_reco_dune35t.fcl .
#echo "services.user.FileCatalogMetadataExtras.RenameTemplate: '' " >> ./minimal_reco_dune_2D.fcl
echo "services.user.TimeService.TriggerOffsetTPC: -1600" >> ./minimal_reco_dune35t.fcl # for consistency
echo "outputs.out1.fileName: 'openclose_reco_dune.root'" >> ./minimal_reco_dune35t.fcl
lar --process-name citest-reco -c ./minimal_reco_dune35t.fcl -s ../lar_ci_openold_detsim_dunetpc/openclose_detsim_dune.root -n 1 -o openclose_reco_dune.root -T openclose_reco_hist_dune.root
