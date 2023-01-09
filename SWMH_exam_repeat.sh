#!/usr/bin/bash
i=1
sum=0
result=0
times=50


i=1
while [ $i -le $times ]; do
    # /usr/bin/time -f %M ./SWMH_array2 zipf_database.txt 100 Minhash.txt 100 2
    /usr/bin/time -f %M ./SWMH_active_index_exam zipf_database.txt 100 Minhash.txt 100 2
    i=$(($i + 1))
done
