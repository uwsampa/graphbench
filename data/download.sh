#!/bin/bash
usage() 
{ 
echo "Usage: $0 [-s <12|16|21|22|25|26>] [-n <facebook|twitter|livejournal|pokec|slashdot08|slashdot09|friendster|twitter-large>]" 1>&2; exit 1; 
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
# 25
TWL=http://an.kaist.ac.kr/~haewoon/release/twitter_social_graph/twitter_rv.tar.gz
# 26
FS=http://snap.stanford.edu/data/bigdata/communities/com-friendster.ungraph.txt.gz


while getopts ":s:n:" o; do
    case "${o}" in
        s)
            s=${OPTARG}
            if [ "${s}" == 12 ] || [ "${s}" == 16 ] || [ "${s}" == 21 ] || [ "${s}" == 22 ] || [ "${s}" == 25 ] || [ "${s}" == 26 ]; then
              :
            else
              echo "dataset with scale ${s} not available"
              usage
            fi
            ;;
        n)
            n=${OPTARG}
            if [ "${n}" == "facebook" ] || [ "${n}" == "twitter" ] || [ "${n}" == "livejournal" ] || [ "${n}" == "pokec" ] || [ "${n}" == "slashdot08" ] || [ "${n}" == "slashdot09" ] || [ "${n}" == "friendster" ] || [ "${n}" == "twitter-large" ]; then 
              :
            else
              echo "dataset with name ${n} not available"
              usage
            fi
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

if [ -n "${s}" ] && [ -z "${n}" ]; then
    # if no scale is given 
    # echo "scale is given and name is not given"
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
    elif [ "${s}" == 25 ]; then
        wget -b -P ./data-downloaded $TWL
    elif [ "${s}" == 26 ]; then
        wget -b -P ./data-downloaded $FS
    else
        echo "no dataset size ${s} available"
        usage
    fi
elif [ -z "${s}" ] && [ -n "${n}" ]; then
    if [ "${n}" == "facebook" ]; then
      wget -b -P ./data-downloaded $FB
    elif [ "${n}" == "twitter" ]; then
      wget -b -P ./data-downloaded $TW
    elif [ "${n}" == "livejournal" ]; then
      wget -b -P ./data-downloaded $LJ
    elif [ "${n}" == "pokec" ]; then
      wget -b -P ./data-downloaded $PC
    elif [ "${n}" == "slashdot08" ]; then
      wget -b -P ./data-downloaded $S8
    elif [ "${n}" == "slashdot09" ]; then
      wget -b -P ./data-downloaded $S9
    elif [ "${n}" == "friendster" ]; then
      wget -b -P ./data-downloaded $FS
    elif [ "${n}" == "twitter-large" ]; then
      wget -b -P ./data-downloaded $TWL
    else
        echo "no dataset called ${n} available"
        usage
    fi
elif [ -n "${s}" ] && [ -n "${n}" ]; then
    # need to double check both
    if [ "${n}" == "facebook" ] && [ "${s}" == 12 ]; then
      wget -b -P ./data-downloaded $FB
    elif [ "${n}" == "twitter" ] && [ "${s}" == 16 ]; then
      wget -b -P ./data-downloaded $TW
    elif [ "${n}" == "livejournal" ] && [ "${s}" == 22 ]; then
      wget -b -P ./data-downloaded $LJ
    elif [ "${n}" == "pokec" ] && [ "${s}" == 21 ]; then
      wget -b -P ./data-downloaded $PC
    elif [ "${n}" == "slashdot08" ] && [ "${s}" == 16 ]; then
      wget -b -P ./data-downloaded $S8
    elif [ "${n}" == "slashdot09" ] && [ "${s}" == 16 ]; then
      wget -b -P ./data-downloaded $S9
    elif [ "${n}" == "friendster" ] && [ "${s}" == 26 ]; then
      wget -b -P ./data-downloaded $FS
    elif [ "${n}" == "twitter-large" ] && [ "${s}" == 25 ]; then
      wget -b -P ./data-downloaded $TWL
    else
        echo "no dataset called ${n} with scale ${s} available"
        usage
    fi
else
    echo "no name or scale given"
    usage
fi