#/bin/bash
i=1
sum=0
result=0
times=100

while [ $i -le $times ]; do
    # result=$(./SWMH_fix_histgram zipf_database_1.txt 100 Minhash.txt 100 2)
    # result=$(./SWMH_fix2 zipf_database_1.txt 100 Minhash.txt 100 2)
    result=$(./SWMH zipf_database_0_5.txt 100 Minhash.txt 100 2 | tail -1)
    sum=$(echo "scale=10; $sum + $result" | bc)
    # i=`expr $i + 1` でもよい
    i=$(($i + 1))
done
printf "%.10f\n" $(echo "scale=10; $sum / $times" | bc)
