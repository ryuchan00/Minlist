#!/usr/bin/bash
# count_minのc1,c2を変化させて計測する
i=1
times=50

sum=0
RecordTimes=""
HEADERS=""
c1s=("2" "8" "16" "32" "64" "128")
c2=28

echo 'zipf_database_1000.txt'
cat zipf_database.txt | awk -F ',' '{print NF}' | head -1
echo 'Minhash_1000.txt'
wc Minhash_1000.txt

# Minlistの探索回数をいくつにするか計測した
# search_limits=("1" "2" "10")
# i=1
# for search_limit in ${search_limits[@]}; do
#     ./SWMH_exam zipf_database.txt 1000 Minhash.txt 1000 $search_limit
#     i=$(($i + 1))
# done

# 基本的なメモリ容量を測定した
# i=1
# while [ $i -le $times ]; do
#     /usr/bin/time -f %M ./SWMH_basic_memory zipf_database.txt 1000
#     i=$(($i + 1))
# done

# i=1
# for c1 in ${c1s[@]}; do
#     HEADERS=$HEADERS$c1
#     if [ $c1 -ne ${c1s[${#c1s[@]} - 1]} ]; then
#         HEADERS=$HEADERS","
#     fi
#     i=$(($i + 1))
# done
# echo $HEADERS

# count minの正確性であるc1,c2を変動させて計測する
# i=1
# while [ $i -le $times ]; do
# for c1 in ${c1s[@]}; do
# i=1
# echo "c1 is ${c1}"
# while [ $i -le $times ]; do
# /usr/bin/time -f %M ./SWMH zipf_database.txt 100 Minhash.txt 100
# /usr/bin/time -f %M ./SWMH_divide_stream_data zipf_database.txt 100 Minhash.txt 100
# /usr/bin/time -f %M ./SWMH_divide_stream_data zipf_database.txt 1000 Minhash.txt 1000
# /usr/bin/time -f %M ./SWMH_array2 zipf_database.txt 100 Minhash.txt 100 2
# /usr/bin/time -f %M ./SWMH_array2 zipf_database.txt 1000 Minhash.txt 1000 2
# RecordTime=$( (/usr/bin/time -f %M ./SWMH_array2 zipf_database.txt 100 Minhash.txt 100 2 $c1 $c2) 2>&1)
# ./SWMH_array2 zipf_database.txt 100 Minhash.txt 100 2 $c2
# RecordTimes=$RecordTimes$RecordTime
# if [ $c1 -ne ${c1s[${#c1s[@]} - 1]} ]; then
#     RecordTimes=$RecordTimes","
# fi
#     i=$(($i + 1))
# done
# echo $RecordTimes
# RecordTimes=""
# i=$(($i + 1))
# done
# done

# 速度計測
i=1
while [ $i -le $times ]; do
    # 従来手法
    # ./SWMH zipf_database_1000.txt 1000 Minhash_1000.txt 1000
    # ./SWMH zipf_database.txt 100 Minhash.txt 100
    # Minlistのスキャン回数指定
    # ./SWMH_array2 zipf_database_1000.txt 1000 Minhash_1000.txt 1000 2
    # Active Index導入
    # ./SWMH_active_index_exam zipf_database_1000.txt 1000 Minhash_1000.txt 1000 2
    # Count-Min Sketch導入
    # ./SWMH_count_min_sketch_report_exam zipf_database_1000.txt 1000 Minhash_1000.txt 1000 2 8 28
    /usr/bin/time -f %M ./SWMH_count_min_sketch_report_exam zipf_database_1000.txt 1000 Minhash_1000.txt 1000 2 16 28
    i=$(($i + 1))
done

exit
