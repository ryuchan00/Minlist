#!/usr/bin/bash
i=1
sum=0
result=0
times=50

echo "繰り返し回数: ${times}"
echo "*--------------------------------------------------*"
i=1
echo "実際のdatasetのサイズ: $(wc zipf_database.txt | awk '{print $1}')"
while [ $i -le $times ]; do
    ./SWMH_cws zipf_database.txt 100 Minhash_cws.txt 100 2 | tail -3 | head -2
    # sum=$(echo "scale=10; $sum + $result" | bc)
    # i=`expr $i + 1` でもよい
    # echo $result
    echo "*--------------------------------------------------*"
    i=$(($i + 1))
    # printf "%.10f\n" $(echo "scale=10; $sum / $times" | bc)
done
