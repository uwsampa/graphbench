#!/bin/bash
usage() 
{ 
#edit the usage!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo "Usage: $0 [-s <16|22>] [-n <name>]" 1>&2; exit 1; 
}

# 12
FB=http://snap.stanford.edu/data/facebook_combined.txt.gz
# 16
TW=http://snap.stanford.edu/data/twitter_combined.txt.gz
# 22
LJ=http://snap.stanford.edu/data/soc-LiveJournal1.txt.gz
# 21
PC=http://snap.stanford.edu/data/soc-pokec-relationships.txt.gz
# 16
S8=http://snap.stanford.edu/data/soc-Slashdot0811.txt.gz
# 16
S9=http://snap.stanford.edu/data/soc-Slashdot0902.txt.gz


while getopts ":s:n:" o; do
    case "${o}" in
        s)
            s=${OPTARG}
            ;;
        n)
            n=${OPTARG}
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

# TODO: add the download part
if [ -n "${s}" ] && [ -z "${n}" ]; then
    # if no scale is given 
    echo "scale is given and name is not given"
    if [ "${s}" == 12 ]; then
        wget -b -P ./data-downloaded $FB
    elif [ "${s}" == 16 ]; then
        wget -b -P ./data-downloaded $TW
        wget -b -P ./data-downloaded $S8
        wget -b -P ./data-downloaded $S9
    elif [ "${s}" == 22 ]; then
        wget -b -P ./data-downloaded $LJ
    elif [ "${s}" == 21 ]; then
        wget -b -P ./data-downloaded $PC
    else
        echo "no dataset size ${s} available"
    fi
elif [ -z "${s}" ] && [ -n "${n}" ]; then
    echo "name is given and scale is not given"
    if [ "${n}" == "facebook" ]; then
          echo "use facebook dataset"
          wget -b -P ./data-downloaded $FB
        elif [ "${n}" == "twitter" ]; then
          echo "use twitter dataset"
          wget -b -P ./data-downloaded $TW
        elif [ "${n}" == "livejournal" ]; then
          echo "use livejournal dataset"
          wget -b -P ./data-downloaded $LJ
        elif [ "${n}" == "pokec" ]; then
          echo "use pokec dataset"
          wget -b -P ./data-downloaded $PC
        elif [ "${n}" == "slashdot08" ]; then
          echo "use slashdot08 dataset"
          wget -b -P ./data-downloaded $S8
        elif [ "${n}" == "slashdot09" ]; then
          echo "use slashdot09 dataset"
          wget -b -P ./data-downloaded $S9
        elif [ "${n}" == "friendster" ]; then
          echo "use friendster dataset"
          echo "need to find the link"
        elif [ "${n}" == "twitter-large" ]; then
          echo "use twitter-large dataset"
          echo "need to find the link"
        else
            "no dataset called ${n} available"
        fi
elif [ -n "${s}" ] && [ -n "${n}" ]; then
    echo "both name and scale are given"
    # need to double check both
else
    echo "no name or scale given"
    usage
fi