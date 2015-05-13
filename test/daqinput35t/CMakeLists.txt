simple_plugin( SplitterAnalyzer "module"
  lbne_daqinput35t
  MF_MESSAGELOGGER
  )

cet_test(splitterInput_t1.sh PREBUILT
	 DATAFILES
	 fcl/SplitterInput_t.fcl
         lbne_r000730_sr01_ten_events.root
         OPTIONAL_GROUPS RELEASE
)

cet_test(splitterInput_t2.sh PREBUILT
	 DATAFILES
	 fcl/SplitterInput_t2.fcl
         lbne_r000730_sr01_ten_events.root
         OPTIONAL_GROUPS RELEASE
)
