#!/bin/bash

CUR_PWD=${PWD}

source /cvmfs/fermilab.opensciencegrid.org/products/common/etc/setups.sh

cd /exp/dune/app/users/vito/CI/generic_ci/
setup -. generic_ci
cd /exp/dune/app/users/vito/CI/lar_ci/
setup -. -j lar_ci

ups active | grep "_ci  "

cd ${CUR_PWD}

#######
# example trigger command for CI Validation build  with token suupport
#
#  trigger_token --build-delay 0 --reason "test tokens" --testmode --token -E sbnd --jobname sbnd_ci_test --workflow CI_VALIDATION_SBND_lite --gridwf-cfg cfg/sbnd/grid_workflow_sbnd_pds_sim_test_vito.cfg -e SBNCI_REF_VERSION=current -e SBNDmodules_extra="LArSoft/larsimrad LArSoft/larsoft SBNSoftware/sbnobj SBNSoftware/sbncode SBNSoftware/larsim"  --revisions "LArSoft/larsimrad@LARSOFT_SUITE_v09_64_01 LArSoft/larsoft@LARSOFT_SUITE_v09_64_01 SBNSoftware/sbnobj@v09_15_02 SBNSoftware/sbncode@feature/icaza_PhotonPropagation SBNSoftware/sbndcode@feature/icaza_PhotonPropagation SBNSoftware/larsim@feature/icaza_PhotonPropagation SBNSoftware/sbnci@feature/icaza_build_fixes" --ci-tests single_gen_quick_test_sbndcode --version feature/ci_jobsub_lite
#

