#/bin/bash
i=1
echo "search_limit        time"

while [ $i -le 50 ]; do
    ./SWMH_exam zipf_database.txt 100 Minhash.txt 100 $i
    # ./SWMH_fix zipf_database.txt 100 Minhash.txt 100 $i
    # i=`expr $i + 1` でもよい
    i=$(($i+1))
done