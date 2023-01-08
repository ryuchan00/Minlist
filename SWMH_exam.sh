#!/usr/bin/bash
i=1
sum=0
result=0
times=10
biases=("1.0")
dataset_size=("10")
array=(SWMH_count_min_sketch_exam2)

sum=0
i=1
while [ $i -le $times ]; do
    ./SWMH_exam zipf_database.txt 100 Minhash.txt 100 ${i}
    i=$(($i + 1))
done
# printf "%.10f\n" $(echo "scale=10; $sum / $times" | bc)
