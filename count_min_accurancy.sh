#!/usr/bin/bash
i=1
times=10
c1=8
c2=32

# echo "繰り返し回数: ${times}"
echo "近似jaccard係数,厳密なjaccard係数,Count-Minのjaccard係数"
while [ $i -le $times ]; do
    # c="/usr/bin/time -f %M ./${v} zipf_database.txt 100 Minhash.txt 100 2 100 100 | tail -n 1"
    ./zipf_generation_database_queri 100 10 100 100 1 >/dev/null 2>&1
    sleep 1
    mv zipf_database.txt zipf_database2.txt
    ./zipf_generation_database_queri 100 10 100 100 1 >/dev/null 2>&1
    sleep 1
    ./SWMH_array2_count_min_report zipf_database.txt 100 Minhash.txt 100 zipf_database2.txt $c1 $c2
    i=$(($i + 1))
done
