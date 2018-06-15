dunetpc/fcl/protodune/fcldirs/rundata/protodune/readme.txt

David Adams
May 2018

This directory holds run data for protodune. The schema are described at

  https://wiki.dunescience.org/wiki/ProtoDUNE_run_configuration#Schema

The tool protoduneRunDataTool may used to fetch this data for a run.
It first takes values from rundata.fcl and then overrides them with the
vlaues in rundataRRRRRR.fcl where RRRRRR is the run number padded to length
six with leading zeros.
