#!/bin/sh
FB=http://snap.stanford.edu/data/facebook_combined.txt.gz
TW=http://snap.stanford.edu/data/twitter_combined.txt.gz
LJ=http://snap.stanford.edu/data/soc-LiveJournal1.txt.gz
PC=http://snap.stanford.edu/data/soc-pokec-relationships.txt.gz
S8=http://snap.stanford.edu/data/soc-Slashdot0811.txt.gz
S9=http://snap.stanford.edu/data/soc-Slashdot0902.txt.gz

if [ "$#" -eq  "0" ];
	then
	wget -b $FB
	wget -b $TW
	wget -b $LJ
	wget -b $PC
	wget -b $S8
	wget -b $S9
else
	for i in "$@"
	do
		CURRENT="$i"
		echo $CURRENT
		# still have bug
		wget -b $i
	done
fi