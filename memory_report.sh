#!/usr/bin/bash
i=1
sum=0
result=0
times=10
biases=("1.0")
dataset_size=("10")
array=(SWMH_count_min_sketch_exam2)

echo "繰り返し回数: ${times}"
echo "ハッシュ関数の数 $(wc Minhash.txt | awk '{print $1}')"
for size in ${dataset_size[@]}; do
    echo "*--------------------------------------------------*"
    for bias in ${biases[@]}; do
        sum=0
        echo "傾き: ${bias}     datasetのサイズ: ${size}"
        echo "実際のdatasetのサイズ: $(wc zipf_database.txt | awk '{print $1}')"
        j=2
        for v in "${array[@]}"; do
            sum=0
            i=1
            echo $v
            while [ $i -le $times ]; do
                # c="/usr/bin/time -f %M ./${v} zipf_database.txt 100 Minhash.txt 100 2 100 100 | tail -n 1"
                ./${v} zipf_database.txt 100 Minhash.txt 100 2 100 100
                # echo $c
                # result=$(eval ${c})
                # echo $result
                # sum=$(echo "scale=10; $sum + $result" | bc)
                # i=`expr $i + 1` でもよい
                i=$(($i + 1))
            done
            # printf "%.10f\n" $(echo "scale=10; $sum / $times" | bc)
        done
    done
done