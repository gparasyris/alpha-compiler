#!/bin/bash

#for i in "03" "06" "09" "12"; do
#for file in /spare/hy459/readoutfile /spare/hy459/iplane.cs.ucr.edu/iplane_logs/2014/$i/*/pl_traces/trace.out.* ;do /spare/hy459/readoutfile $file | awk '{ if (/destination/) print "destination";print $2;}';done ;done> /spare/kerasei/1_files/allrouters.rtf



#awk '!seen [$0]++' <1_files/allrouters.rtf | awk '!/0.0.0.0/{print}' |awk '!/destination/{print}' > 1_files/nonDuplicates.rtf



#awk 'END { print "The number of routers is: " NR }' 1_files/nonDuplicates.rtf > 1_files/question_1_all.txt


make

make parser

#for file in /spare/hy459/readoutfile /net/fistiki/spare/hy459/iplane.cs.ucr.edu/iplane_logs/2014/12/*/pl_traces/trace.out.* ;do /net/fistiki/spare/hy459/readoutfile $file | awk '{ if (/destination/) print "destination";print $2;}';done | awk '!seen [$0]++' | awk '!/0.0.0.0/{print}' |awk '!/destination/{print}' | awk 'END { print "The number of routers is: " NR }' > 1_files/question_1_december.txt


#rm -rf *.rtf

