simple_plugin( SplitterAnalyzer "module"
  lbne_daqinput35t
  MF_MESSAGELOGGER
  )

cet_test(SplitterInput_t1 HANDBUILT
         TEST_EXEC lar
	 TEST_ARGS --rethrow-all --config SplitterInput_t.fcl
	 DATAFILES
	 fcl/SplitterInput_t.fcl
         /scratch/knoepfel/lbne_r000730_sr01_20150317T160905_ten_events.root
         /scratch/knoepfel/lbne_r000730_sr01_20150317T160905_ten_events_2.root
         /scratch/knoepfel/lbne_r000730_sr02_20150317T160905_ten_events.root
)

cet_test(SplitterInput_t2 HANDBUILT
         TEST_EXEC lar
	 TEST_ARGS --rethrow-all --config SplitterInput_t2.fcl
	 DATAFILES
	 fcl/SplitterInput_t2.fcl
         /scratch/knoepfel/lbne_r000730_sr01_20150317T160905_ten_events.root
         /scratch/knoepfel/lbne_r000730_sr01_20150317T160905_ten_events_2.root
         /scratch/knoepfel/lbne_r000730_sr02_20150317T160905_ten_events.root
)



