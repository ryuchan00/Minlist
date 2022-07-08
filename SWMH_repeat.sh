#!/usr/bin/bash
i=1
sum=0
result=0
times=50
biases=("0.0" "0.5" "1.0")
dataset_size=("10" "100" "1000" "10000")

echo "繰り返し回数: ${times}"
echo "ハッシュ関数の数 $(wc Minhash.txt | awk '{print $1}')"
for size in ${dataset_size[@]}; do
    echo "*--------------------------------------------------*"
    for bias in ${biases[@]}; do
        sum=0
        i=1
        echo "傾き: ${bias}     datasetのサイズ: ${size}"
        echo "実際のdatasetのサイズ: $(wc zipf_database_${size}_${bias}.txt | awk '{print $1}')"
        while [ $i -le $times ]; do
            result=$(./SWMH_fix_histgram zipf_database_${size}_${bias}.txt 100 Minhash.txt 100 2 | tail -1)
            sum=$(echo "scale=10; $sum + $result" | bc)
            # i=`expr $i + 1` でもよい
            i=$(($i + 1))
        done
        printf "%.10f\n" $(echo "scale=10; $sum / $times" | bc)
    done
done
