## コンパイル方法

```bash
# O2オプションをつける
g++ -O2 -o SWMH SWMH.cpp
```

## データの作り方からの一連の流れ

```bash
# データーベース作成
g++ -O2 -o zipf_generation_database_queri zipf_generation_database_queri.cpp
# ./zipf_generation_database_queri ウィンドウサイズ databaseのdata数 多重度上限 要素の種類数  傾きalpha
./zipf_generation_database_queri 100 10 10 100 1

# Min-hashの割り当て値生成
g++ -O2 -o gminhash2 gminhash2.cpp
# ./gminhash2 ハッシュ関数の数　要素の種類数 多重度上限 シード値
./gminhash2 10 100 10 1

# (3)バッチSWMHの実行時間の計測
g++ -O2 -o BSWMH BSWMH_exam.cpp
# ./BSWMH database.txt　SWの数　Minhash.txt マルチセットの上限 更新の間隔
./BSWMH database.txt 100 Minhash.txt 100 10
```
