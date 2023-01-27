#!/usr/bin/bash
# count_minのc1,c2を変化させて計測する
i=1
times=10

sum=0
RecordTimes=""
HEADERS=""
c1s=("1" "2" "4" "8")
c2=20

echo 'zipf_database.txt'
cat zipf_database.txt | awk -F ',' '{print NF}' | head -1
echo 'Minhash.txt'
wc Minhash.txt

search_limits=("1" "2" "10")
i=1
for search_limit in ${search_limits[@]}; do
    ./SWMH_exam zipf_database.txt 1000 Minhash.txt 1000 $search_limit
    i=$(($i + 1))
done

# i=1
# for c1 in ${c1s[@]}; do
#     HEADERS=$HEADERS$c1
#     if [ $c1 -ne ${c1s[${#c1s[@]} - 1]} ]; then
#         HEADERS=$HEADERS","
#     fi
#     i=$(($i + 1))
# done
# echo $HEADERS

i=1
# while [ $i -le $times ]; do
#     for c1 in ${c1s[@]}; do
#         # /usr/bin/time -f %M ./SWMH zipf_database.txt 100 Minhash.txt 100
#         # /usr/bin/time -f %M ./SWMH_divide_stream_data zipf_database.txt 100 Minhash.txt 100
#         # /usr/bin/time -f %M ./SWMH_divide_stream_data zipf_database.txt 1000 Minhash.txt 1000
#         # /usr/bin/time -f %M ./SWMH_array2 zipf_database.txt 100 Minhash.txt 100 2
#         # /usr/bin/time -f %M ./SWMH_array2 zipf_database.txt 1000 Minhash.txt 1000 2
#         RecordTime=$( (/usr/bin/time -f %M ./SWMH_count_min_sketch_report_exam zipf_database.txt 1000 Minhash.txt 1000 2 $c1 $c2) 2>&1)
#         RecordTimes=$RecordTimes$RecordTime
#         if [ $c1 -ne ${c1s[${#c1s[@]} - 1]} ]; then
#             RecordTimes=$RecordTimes","
#         fi
#     done
#     echo $RecordTimes
#     RecordTimes=""
#     i=$(($i + 1))
# done

exit
