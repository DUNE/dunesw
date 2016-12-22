#!/bin/bash

LARVERSION=v06_15_00

DOITSCRIPT=doit.sh

IFS=""
function genfhicl {
    echo "MCTest_mixer_gen.fcl"
}
function genxml {
    echo "mixer_gen.xml"
}
function genname {
    echo "mixer"
}
function g4fhicl {
    echo "MCTest_mixer_g4_$1.fcl"
}
function g4xml {
    echo "mixer_g4_$1.xml"
}
function g4name {
    echo "mixer_$1"
}
function detsimfhicl {
    echo "MCTest_mixer_detsim.fcl"
}
function detsimxml {
    echo "mixer_detsim_$1.xml"
}
function detsimname {
    echo "mixer_$1"
}
function overlayfhicl {
    echo "MCTest_mixer_dataoverlay_mcscale$1.fcl"
}
function wrapoverlayfhicl {
    echo "run_MCTest_mixer_dataoverlay_mcscale$1.fcl"
}
function overlayxml {
    echo "mixer_dataoverlay_$1_mcscale$2.xml"
}
function overlayname {
    echo "mixer_$1_mcscale$2"
}
function robustfhicl {
    echo "MCTest_mixer_robust.fcl"
}
function robustxml {
    echo "mixer_robust_$1_mcscale$2.xml"
}
function robustname {
    echo "mixer_$1_mcscale$2"
}
function anafhicl {
    echo "MCTest_mixer_ana_mcscale$1.fcl"
}
function anaxml {
    echo "mixer_ana_$1_mcscale$2.xml"
}
function ananame {
    echo "mixer_$1_mcscale$2"
}
function write_header {
    cat <<EOF > $1
<?xml version="1.0"?>
<!DOCTYPE project [
<!ENTITY release "${LARVERSION}">
<!ENTITY file_type "mc">
<!ENTITY run_type "physics">
<!ENTITY name "$2">
<!ENTITY tag "mthiesse">
]>
<project name="&name;">
<group>dune</group>
<numevents>100000000</numevents>
<os>SL6</os>
<resource>DEDICATED,OPPORTUNISTIC</resource>
<larsoft>
   <tag>&release;</tag>
   <qual>e10:prof</qual>
   <local>/dune/app/users/mthiesse/larDev/${LARVERSION}.tar</local>
</larsoft>
<parameter name ="MCName">mixer</parameter>
<parameter name ="MCDetectorType">35t</parameter>
<parameter name ="MCGenerators">CRY_single</parameter>
EOF
}
function write_footer {
    cat <<EOF >> $1
<filetype>&file_type;</filetype>
<runtype>&run_type;</runtype>
</project>
EOF
}

declare -a gensubmitcommands
declare -a gencheckcommands
declare -a gencleancommands
declare -a genmakeupcommands
declare -a g4submitcommands
declare -a g4checkcommands
declare -a g4cleancommands
declare -a g4makeupcommands
declare -a detsimsubmitcommands
declare -a detsimcheckcommands
declare -a detsimcleancommands
declare -a detsimmakeupcommands
declare -a overlaysubmitcommands
declare -a overlaycheckcommands
declare -a overlaycleancommands
declare -a overlaymakeupcommands
declare -a robustsubmitcommands
declare -a robustcheckcommands
declare -a robustcheckanacommands
declare -a robustcleancommands
declare -a robustmakeupcommands
declare -a robusthaddcommands
declare -a anasubmitcommands
declare -a anacheckcommands
declare -a anacleancommands
declare -a anamakeupcommands
declare -a anahaddcommands

write_header $(genxml) $(genname)
cat <<EOF >> $(genxml)
<stage name="gen">
   <fcl>$(genfhicl)</fcl>
   <outdir>/pnfs/dune/scratch/users/mthiesse/MC/&release;/gen/&name;</outdir>
   <workdir>/pnfs/dune/scratch/users/mthiesse/MC/work/&release;/gen/&name;</workdir>
   <output>MCTest_mixer_\${PROCESS}_%tc_gen.root</output>
   <numjobs>1000</numjobs>
   <datatier>generated</datatier>
   <defname>&name;_&tag;_gen</defname>
</stage>
EOF
write_footer $(genxml)

gensubmitcommands=(${gensubmitcommands[@]} 
    "echo 'Submitting $(genxml):';project.py --xml $(genxml) --stage gen --submit")
gencheckcommands=(${gencheckcommands[@]}
    "echo 'Checking $(genxml):' > $(genname).out;project.py --xml $(genxml) --stage gen --check >> $(genname).out 2>&1 &")
gencleancommands=(${gencleancommands[@]}
    "echo 'Cleaning $(genxml):';project.py --xml $(genxml) --stage gen --clean")
genmakeupcommands=(${genmakeupcommands[@]}
    "echo 'Makeup $(genxml):';project.py --xml $(genxml) --stage gen --makeup")

for item in "1ms" "2ms" "3ms" "5ms" "8ms";
do
    set -- $item
    elife=$1
    
    write_header $(g4xml $elife) $(g4name $elife)
    cat <<EOF >> $(g4xml $elife)
<stage name="g4">
   <fcl>$(pwd)/$(g4fhicl $elife)</fcl>
   <inputlist>/pnfs/dune/scratch/users/mthiesse/MC/&release;/gen/$(genname)/files.list</inputlist>
   <outdir>/pnfs/dune/scratch/users/mthiesse/MC/&release;/g4/&name;</outdir>
   <workdir>/pnfs/dune/scratch/users/mthiesse/MC/work/&release;/g4/&name;</workdir>
   <output>MCTest_mixer_\${PROCESS}_%tc_g4.root</output>
   <numjobs>1000</numjobs>
   <datatier>simulated</datatier>
   <defname>&name;_&tag;_g4</defname>
</stage>
EOF
   write_footer $(g4xml $elife)

   echo '#include "MCTest_mixer_g4.fcl"' > $(g4fhicl $elife)
   echo 'services.DetectorPropertiesService.Electronlifetime: '${elife:0:1}000 >> $(g4fhicl $elife)
   
   g4submitcommands=(${g4submitcommands[@]}
       "echo 'Submitting $(g4xml $elife):';project.py --xml $(g4xml $elife) --stage g4 --submit")
   g4checkcommands=(${g4checkcommands[@]}
       "echo 'Checking $(g4xml $elife):' > $(g4name $elife).out;project.py --xml $(g4xml $elife) --stage g4 --check >> $(g4name $elife).out 2>&1 &")
   g4cleancommands=(${g4cleancommands[@]}
       "echo 'Cleaning $(g4xml $elife):';project.py --xml $(g4xml $elife) --stage g4 --clean")
   g4makeupcommands=(${g4makeupcommands[@]}
       "echo 'Makeup $(g4xml $elife):';project.py --xml $(g4xml $elife) --stage g4 --makeup")
   
   write_header $(detsimxml $elife) $(detsimname $elife)
   cat <<EOF >> $(detsimxml $elife)
<stage name="detsim">
   <fcl>$(detsimfhicl)</fcl>
   <inputlist>/pnfs/dune/scratch/users/mthiesse/MC/&release;/g4/$(g4name $elife)/files.list</inputlist>
   <outdir>/pnfs/dune/scratch/users/mthiesse/MC/&release;/detsim/&name;</outdir>
   <workdir>/pnfs/dune/scratch/users/mthiesse/MC/work/&release;/detsim/&name;</workdir>
   <output>MCTest_mixer_\${PROCESS}_%tc_detsim.root</output>
   <numjobs>1000</numjobs>
   <datatier>detector-simulated</datatier>
   <defname>&name;_&tag;_detsim</defname>
</stage>
EOF
   write_footer $(detsimxml $elife)

   detsimsubmitcommands=(${detsimsubmitcommands[@]}
       "echo 'Submitting $(detsimxml $elife):';project.py --xml $(detsimxml $elife) --stage detsim --submit | grep -v Adding")
   detsimcheckcommands=(${detsimcheckcommands[@]}
       "echo 'Checking $(detsimxml $elife):' > $(detsimname $elife).out;project.py --xml $(detsimxml $elife) --stage detsim --check >> $(detsimname $elife).out 2>&1 &")
   detsimcleancommands=(${detsimcleancommands[@]}
       "echo 'Cleaning $(detsimxml $elife):';project.py --xml $(detsimxml $elife) --stage detsim --clean")
   detsimmakeupcommands=(${detsimmakeupcommands[@]}
       "echo 'Makeup $(detsimxml $elife):';project.py --xml $(detsimxml $elife) --stage detsim --makeup")
   
   ##for otheritem in "0.5" "1.0" "1.5" "2.0";
   for otheritem in "0.5" "1.0" "1.5" "2.0" "2.5" "3.0" "3.5" "4.0" "4.5" "5.0" "5.5" "6.0" "7.0" "8.0" "9.0" "10.0";
   do
       set -- $otheritem
       scale=$1
  
       write_header $(overlayxml $elife $scale) $(overlayname $elife $scale)
       cat <<EOF >> $(overlayxml $elife $scale)
<stage name="dataoverlay">
   <fcl>$(pwd)/$(overlayfhicl $scale)</fcl>
   <inputlist>/pnfs/dune/scratch/users/mthiesse/MC/&release;/detsim/$(detsimname $elife)/files.list</inputlist>
   <outdir>/pnfs/dune/scratch/users/mthiesse/MC/&release;/dataoverlay/&name;</outdir>
   <workdir>/pnfs/dune/scratch/users/mthiesse/MC/work/&release;/detsim/&name;</workdir>
   <output>MCTest_mixer_\${PROCESS}_%tc_dataoverlay.root</output>
   <numjobs>1000</numjobs>
   <datatier>detector-simulated</datatier>
   <defname>&name;_&tag;_dataoverlay</defname>
</stage>
EOF
       write_footer $(overlayxml $elife $scale)

       echo '#include "MCTest_mixer_dataoverlay.fcl"' > $(overlayfhicl $scale)
       echo 'physics.filters.mixer.detail.DefaultMCRawDigitScale: '$scale >> $(overlayfhicl $scale)

       overlaysubmitcommands=(${overlaysubmitcommands[@]}
	   "echo 'Submitting $(overlayxml $elife $scale):';
DATETIME=\$(date +'%Y-%m-%d_%H-%M-%S');
DEFNAME='goodruns_35ton_sliced_mthiesse';
PROJECTNAME=mthiesse_\${DEFNAME}_${elife}_mcscale${scale}_\${DATETIME};
samweb -e dune -v start-project --defname=\$DEFNAME \$PROJECTNAME;
echo 'physics.filters.mixer.detail.SamProject: \"'\$PROJECTNAME'\"' >> $(overlayfhicl $scale);
project.py --xml $(overlayxml $elife $scale) --stage dataoverlay --submit")
       overlaycheckcommands=(${overlaycheckcommands[@]}
	   "echo 'Checking $(overlayxml $elife $scale):' > $(overlayname $elife $scale).out;project.py --xml $(overlayxml $elife $scale) --stage dataoverlay --check >> $(overlayname $elife $scale).out 2>&1 &")
       overlaycleancommands=(${overlaycleancommands[@]}
	   "echo 'Cleaning $(overlayxml $elife $scale):';project.py --xml $(overlayxml $elife $scale) --stage dataoverlay --clean")
       overlaymakeupcommands=(${overlaymakeupcommands[@]}
	   "echo 'Makeup $(overlayxml $elife $scale):';project.py --xml $(overlayxml $elife $scale) --stage dataoverlay --makeup")
       
       write_header $(robustxml $elife $scale) $(robustname $elife $scale)
       cat <<EOF >> $(robustxml $elife $scale)
<stage name="robust">
   <fcl>$(robustfhicl)</fcl>
   <inputlist>/pnfs/dune/scratch/users/mthiesse/MC/&release;/dataoverlay/$(overlayname $elife $scale)/files.list</inputlist>
   <outdir>/pnfs/dune/scratch/users/mthiesse/MC/&release;/robust/&name;</outdir>
   <workdir>/pnfs/dune/scratch/users/mthiesse/MC/work/&release;/robust/&name;</workdir>
   <output>MCTest_mixer_\${PROCESS}_%tc_robust.root</output>
   <numjobs>1000</numjobs>
   <datatier>full-reconstructed</datatier>
   <defname>&name;_&tag;_robust</defname>
</stage>
EOF
       write_footer $(robustxml $elife $scale)

       robustsubmitcommands=(${robustsubmitcommands[@]}
	   "echo 'Submitting $(robustxml $elife $scale):';project.py --xml $(robustxml $elife $scale) --stage robust --submit")
       robustcheckcommands=(${robustcheckcommands[@]}
	   "echo 'Checking $(robustxml $elife $scale):' > $(robustname $elife $scale).out;project.py --xml $(robustxml $elife $scale) --stage robust --check >> $(robustname $elife $scale).out 2>&1 &")
       robustcheckanacommands=(${robustcheckanacommands[@]}
	   "echo 'Checking $(robustxml $elife $scale) histogram files:' > $(robustname $elife $scale)_hist.out;project.py --xml $(robustxml $elife $scale) --stage robust --checkana >> $(robustname $elife $scale)_hist.out 2>&1 &")
       robustcleancommands=(${robustcleancommands[@]}
	   "echo 'Cleaning $(robustxml $elife $scale):';project.py --xml $(robustxml $elife $scale) --stage robust --clean")
       robustmakeupcommands=(${robustmakeupcommands[@]}
	   "echo 'Makeup $(robustxml $elife $scale):';project.py --xml $(robustxml $elife $scale) --stage robust --makeup")
       robusthaddcommands=(${robusthaddcommands[@]}
	   "hadd -f -k /dune/data/users/mthiesse/robust_$(robustname $elife $scale)_hist.root @/pnfs/dune/scratch/users/mthiesse/MC/${LARVERSION}/robust/$(robustname $elife $scale)/filesana.list")

       write_header $(anaxml $elife $scale) $(ananame $elife $scale)
       cat <<EOF >> $(anaxml $elife $scale)
<stage name="ana">
   <fcl>$(pwd)/$(anafhicl $scale)</fcl>
   <inputlist>/pnfs/dune/scratch/users/mthiesse/MC/&release;/robust/$(robustname $elife $scale)/files.list</inputlist>
   <outdir>/pnfs/dune/scratch/users/mthiesse/MC/&release;/ana/&name;</outdir>
   <workdir>/pnfs/dune/scratch/users/mthiesse/MC/work/&release;/ana/&name;</workdir>
   <TFileName>MCTest_mixer_\${PROCESS}_%tc_ana_hist.root</TFileName>
   <numjobs>1000</numjobs>
   <datatier>full-reconstructed</datatier>
   <defname>&name;_&tag;_ana</defname>
</stage>
EOF
       write_footer $(anaxml $elife $scale)

       echo '#include "MCTest_mixer_ana.fcl"' > $(anafhicl $scale)
       echo 'physics.analyzers.robustmcana.PreviousMCScale: '$scale >> $(anafhicl $scale)

       anasubmitcommands=(${anasubmitcommands[@]}
           "echo 'Submitting $(anaxml $elife $scale):';project.py --xml $(anaxml $elife $scale) --stage ana --submit")
       anacheckcommands=(${anacheckcommands[@]}
           "echo 'Checking $(anaxml $elife $scale):' > $(ananame $elife $scale).out;project.py --xml $(anaxml $elife $scale) --stage ana --checkana >> $(ananame $elife $scale).out 2>&1 &")
       anacleancommands=(${anacleancommands[@]}
           "echo 'Cleaning $(anaxml $elife $scale):';project.py --xml $(anaxml $elife $scale) --stage ana --clean")
       anamakeupcommands=(${anamakeupcommands[@]}
           "echo 'Makeup $(anaxml $elife $scale):';project.py --xml $(anaxml $elife $scale) --stage ana --makeup")
       anahaddcommands=(${anahaddcommands[@]}
	   "hadd -f -k /dune/data/users/mthiesse/ana_$(ananame $elife $scale)_hist.root @/pnfs/dune/scratch/users/mthiesse/MC/${LARVERSION}/ana/$(ananame $elife $scale)/filesana.list")

   done
done

echo "#!/bin/bash" > $DOITSCRIPT
echo "kx509;voms-proxy-init -noregen -rfc -voms dune:/dune/Role=Analysis;" >> $DOITSCRIPT
echo "function submit_gen {" >> $DOITSCRIPT
for ((i=0; i < ${#gensubmitcommands[@]}; i++)); do
    echo "${gensubmitcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function check_gen {" >> $DOITSCRIPT
for ((i=0; i < ${#gencheckcommands[@]}; i++)); do
    echo "${gencheckcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function clean_gen {" >> $DOITSCRIPT
for ((i=0; i < ${#gencleancommands[@]}; i++)); do
    echo "${gencleancommands[$i]}" >> $DOITSCRIPT
done
echo "}
function makeup_gen {" >> $DOITSCRIPT
for ((i=0; i < ${#genmakeupcommands[@]}; i++)); do
    echo "${genmakeupcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function submit_g4 {" >> $DOITSCRIPT
for ((i=0; i < ${#g4submitcommands[@]}; i++)); do
    echo "${g4submitcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function check_g4 {" >> $DOITSCRIPT
for ((i=0; i < ${#g4checkcommands[@]}; i++)); do
    echo "${g4checkcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function clean_g4 {" >> $DOITSCRIPT
for ((i=0; i < ${#g4cleancommands[@]}; i++)); do
    echo "${g4cleancommands[$i]}" >> $DOITSCRIPT
done
echo "}
function makeup_g4 {" >> $DOITSCRIPT
for ((i=0; i < ${#g4makeupcommands[@]}; i++)); do
    echo "${g4makeupcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function submit_detsim {" >> $DOITSCRIPT
for ((i=0; i < ${#detsimsubmitcommands[@]}; i++)); do
    echo "${detsimsubmitcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function check_detsim {" >> $DOITSCRIPT
for ((i=0; i < ${#detsimcheckcommands[@]}; i++)); do
    echo "${detsimcheckcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function clean_detsim {" >> $DOITSCRIPT
for ((i=0; i < ${#detsimcleancommands[@]}; i++)); do
    echo "${detsimcleancommands[$i]}" >> $DOITSCRIPT
done
echo "}
function makeup_detsim {" >> $DOITSCRIPT
for ((i=0; i < ${#detsimmakeupcommands[@]}; i++)); do
    echo "${detsimmakeupcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function submit_dataoverlay {" >> $DOITSCRIPT
for ((i=0; i < ${#overlaysubmitcommands[@]}; i++)); do
    echo "${overlaysubmitcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function check_dataoverlay {" >> $DOITSCRIPT
for ((i=0; i < ${#overlaycheckcommands[@]}; i++)); do
    echo "${overlaycheckcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function clean_dataoverlay {" >> $DOITSCRIPT
for ((i=0; i < ${#overlaycleancommands[@]}; i++)); do
    echo "${overlaycleancommands[$i]}" >> $DOITSCRIPT
done
echo "}
function makeup_dataoverlay {" >> $DOITSCRIPT
for ((i=0; i < ${#overlaymakeupcommands[@]}; i++)); do
    echo "${overlaymakeupcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function submit_robust {" >> $DOITSCRIPT
for ((i=0; i < ${#robustsubmitcommands[@]}; i++)); do
    echo "${robustsubmitcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function check_robust {" >> $DOITSCRIPT
for ((i=0; i < ${#robustcheckcommands[@]}; i++)); do
    echo "${robustcheckcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function checkana_robust {" >> $DOITSCRIPT
for ((i=0; i < ${#robustcheckanacommands[@]}; i++)); do
    echo "${robustcheckanacommands[$i]}" >> $DOITSCRIPT
done
echo "}
function clean_robust {" >> $DOITSCRIPT
for ((i=0; i < ${#robustcleancommands[@]}; i++)); do
    echo "${robustcleancommands[$i]}" >> $DOITSCRIPT
done
echo "}
function makeup_robust {" >> $DOITSCRIPT
for ((i=0; i < ${#robustmakeupcommands[@]}; i++)); do
    echo "${robustmakeupcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function hadd_robust {" >> $DOITSCRIPT
for ((i=0; i < ${#robusthaddcommands[@]}; i++)); do
    echo "${robusthaddcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function submit_ana {" >> $DOITSCRIPT
for ((i=0; i < ${#anasubmitcommands[@]}; i++)); do
    echo "${anasubmitcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function check_ana {" >> $DOITSCRIPT
for ((i=0; i < ${#anacheckcommands[@]}; i++)); do
    echo "${anacheckcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function clean_ana {" >> $DOITSCRIPT
for ((i=0; i < ${#anacleancommands[@]}; i++)); do
    echo "${anacleancommands[$i]}" >> $DOITSCRIPT
done
echo "}
function makeup_ana {" >> $DOITSCRIPT
for ((i=0; i < ${#anamakeupcommands[@]}; i++)); do
    echo "${anamakeupcommands[$i]}" >> $DOITSCRIPT
done
echo "}
function hadd_ana {" >> $DOITSCRIPT
for ((i=0; i < ${#anahaddcommands[@]}; i++)); do
    echo "${anahaddcommands[$i]}" >> $DOITSCRIPT
done
echo "}" >> $DOITSCRIPT


unset gensubmitcommands
unset gencheckcommands
unset gencleancommands
unset genmakeupcommands
unset g4submitcommands
unset g4checkcommands
unset g4cleancommands
unset g4makeupcommands
unset detsimsubmitcommands
unset detsimcheckcommands
unset detsimcleancommands
unset detsimmakeupcommands
unset overlaysubmitcommands
unset overlaycheckcommands
unset overlaycleancommands
unset overlaymakeupcommands
unset robustsubmitcommands
unset robustcheckcommands
unset robustcheckanacommands
unset robustcleancommands
unset robustmakeupcommands
unset robusthaddcommands
unset anasubmitcommands
unset anacheckcommands
unset anacleancommands
unset anamakeupcommands
unset anahaddcommands