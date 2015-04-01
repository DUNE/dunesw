simple_plugin( SplitterAnalyzer "module"
  lbne_daqinput35t
  )

cet_test(SplitterInput_t HANDBUILT
         TEST_EXEC lar
	 TEST_ARGS --rethrow-all --config SplitterInput_t.fcl
	 DATAFILES
	 fcl/SplitterInput_t.fcl
         /scratch/knoepfel/lbne_r000730_sr01_20150317T160905_ten_events.root
         /scratch/knoepfel/lbne_r000730_sr01_20150317T160905_ten_events_2.root
         /scratch/knoepfel/lbne_r000730_sr02_20150317T160905_ten_events.root
)
