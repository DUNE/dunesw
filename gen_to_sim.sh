trigger_token --role ci --token -i dune --build-delay 0 --quals e26:prof \
    -e DUNEmodules_extra="LArSoft/larsoft DUNE/dunesw" \
    --revisions "LArSoft/larsoft@v10_04_07 DUNE/dunesw@feature/by_CIval" \
    --workflow CI_VALIDATION_DUNE_lite --jobname dune_ci_test \
    --gridwf-cfg cfg/dune/lbl/grid_workflow_dunehd_1x2x6_lbl_all.cfg \
    --version feature/chappell_vd_ci
