#/bin/bash
i=2
echo "search_limit,time"

while [ $i -le 500 ]; do
    # ./SWMH_exam zipf_database.txt 10000 Minhash.txt 10 $i
    ./SWMH_fix zipf_database.txt 10000 Minhash.txt 10 $i
    i=`expr $i + 2`
done