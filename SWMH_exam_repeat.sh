#!/usr/bin/bash
# ActiveIndexとCountMinSketch比較用
i=1
sum=0
result=0
times=50
c1=2
c2=30

echo 'zipf_database.txt'
cat zipf_database.txt | awk -F ',' '{print NF}' | head -1
echo 'Minhash.txt'
wc Minhash.txt

i=1
while [ $i -le $times ]; do
    /usr/bin/time -f %M ./SWMH_array2 zipf_database.txt 1000 Minhash.txt 1000 2
    # /usr/bin/time -f %M ./SWMH_active_index_exam zipf_database.txt 1000 Minhash.txt 1000 2
    # /usr/bin/time -f %M ./SWMH_count_min_sketch_report_exam zipf_database.txt 100 Minhash.txt 100 2 $c1 $c2
    i=$(($i + 1))
done
