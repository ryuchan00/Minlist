/*Min-Hashの作成*/



///////////////////////////////////////////////////////////////////////////////////////////////////////
// ./gmihash2 ハッシュ関数の数　データベースの要素の種類数 マルチセットの要素の数の上限 シード値//
// 元データの要素をランダムに組み合わせてデータベースを作る関数                                //
///////////////////////////////////////////////////////////////////////////////////////////////////////



#include<iostream>
#include<vector>
#include<algorithm>
#include<stdlib.h>
#include<time.h>
#include<fstream>

/*Min-Hashを1つ作成*/
//要素種類数hashsizeを指定し、
//ランダムに並び替える
//例)hashsize = 7 
//max = 7
//hash1 : 0 1 2 3 4 5 6
//hash2 :
//↓ x <- 0〜6(max - 1)の中からランダム
//x = 2
//hash1[2]を取り出し、hash2の末尾に入れる
//hash1 : 0 1 3 4 5 6
//hash2 : 2
//max = 6
//↓ x <- 0〜5(max - 1)の中からランダム
//x = 4
//hash1[4]を取り出し、hash2の末尾に入れる
//hash1 : 0 1 3 4 6
//hash2 : 2 5
//max = 5
//↓
//最終的にできたhash2を返す
std::vector<int> make_hash(int hashsize)
{
    int max = hashsize;
    int max2=max;
    int x;
    std::vector<int> hash1,hash2;
    /*hash1の初期設定*/
    for (int i = 0; i < max; i++)
    {
        hash1.push_back(i);
    }
    
    for (int i = 0; i < max2; i++)
    {
        x = rand() % max;
        hash2.push_back(hash1[x]);
        hash1.erase(hash1.begin() + x);
        max--;
    }
    return hash2;
}


/*Min-Hashを複数作成*/
//num_of_hash個のハッシュ関数を作成
std::vector< std::vector<int> > make_minhash(int num_of_hash,int hashsize)
{
    std::vector< std::vector<int> > hash_function;
    for (int i = 0; i < num_of_hash; i++)
    {
        hash_function.push_back(make_hash(hashsize));
    }
    return hash_function;
}


int main(int argc,char* argv[])
{
    int num_of_hash=atoi(argv[1]);//ハッシュ関数
    int vm=atoi(argv[2]);
    int malti=atoi(argv[3]);//重複度の上限
    srand(atoi(argv[4]));//シード値
    
    //使うのはvm,num_of_hash
    /*Min-Hash作成*/
    int vmm=vm*malti;
    
    std::vector< std::vector<int> > minhash = make_minhash(num_of_hash,vmm);
    
    
    std::ofstream ofs("Minhash.txt");//Minhash.txtに出力
    
    for(int i = 0;i < num_of_hash;i++)
    {
        for(int j = 0;j < vmm;j++)
        {
            ofs << minhash[i][j];
            if(j != vmm - 1)
            {
                ofs<< ",";
            }
            //数字,数字,・・・
            //のように出力
        }
        ofs << "" << std::endl;//1つのMin-Hashを出力後改行
    }
    
    return 0;
}
