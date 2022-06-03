/*Min Hashベースの近似解法MHI*/

/*
 先行研究論文
 Xu, X., Gao, C., Pei, J., Wang, K., Al-Barakati, A.: Continuous similarity
 search for evolving queries. Knowl. Inf. Syst. 48(3), 649–678 (2016)
 */
#include"kyotsu.h"
#include"minhash.h"
#include"contents.h"
using namespace std;
struct Mincontents{
    int label;
    int min;
};

int main(int argc,char* argv[])
{
    int t = 0,x,y,j,val;
    vector<int> queri;//クエリ
    vector< vector<int> > database,dsort;//データベース
    
    
    char* dbname = argv[1];//database.txt
        char* qname = argv[2];//queri.txt
     queri = readqueri(qname); //クエリ作成
    database = readdatabase(dbname); //データベース作成
    
    /*パラメータ*/
    int r = database.size();//データ数
    //int r = 10;
    deque< deque<int> > dt(r);//スライディングウインドウ
    int k = atoi(argv[3]);//top-kのk
    int w = atoi(argv[4]);//ウインドウサイズ
    int dmax = 1000 + w;//ストリームデータの長さ
    
    vector< vector<int> > minhash;
    vector< vector<int> > database_hashvalue(r);
    vector< vector<int> > kara(r);
    vector<int> phashval;//前時刻のハッシュ値
    vector<int> hashval;//現時刻のハッシュ値
    vector<int>::iterator it;
    vector<struct ranking> list(r);//類似度を示すリスト
    
    /*
     先行研究論文Algorithmでは、
     類似度を(ハッシュ衝突回数)/(ハッシュ関数の数)
     で近似していた。実装上は(ハッシュ衝突回数)
     を類似度とする。
     */
    
    priority_queue<ranking> v;//minヒープ
    /*
     cout << "q :";
     printdata(queri);
     */
    
    //   dt=make_d0(w,database,r);
    
    /*リストの初期設定*/
    for(int i = 0;i < r; i++)
    {
        list[i].sim = 0;
        list[i].id = i;
    }
    char* mhname = argv[5];//Minhash.txt
    minhash = readminhash(mhname);//ハッシュ関数の読み込み
    int num_of_hash = minhash.size();//ハッシュ関数の数
    int vmw = minhash[0].size();//要素種類数 × 多重度の数
    int malti=atoi(argv[6]); //wの中の要素の数の上限
    int vm = vmw/malti; //要素の種類数,gminhash2のと同じでないといけない
    
    
    /*Min-hashに用いるランダムの値のテーブル*/
    //vector<vector<vector<int>>> fx(num_of_hash);//テーブル
    // vector< vector<int> > invalue(500);
    vector<vector<vector<int> > > fx(num_of_hash,vector<vector<int> >(vm,vector<int>(malti+1,9999)));
    
    deque< deque<int> > histgram(r, deque<int>(vm,0));//初期値0
    
    //最小値
    struct Mincontents Min;
    Min.label = 99999;
    Min.min = 100000;
    vector<vector<Mincontents> > minimum_of_allocation(r,vector<Mincontents>(num_of_hash,Min));
    
    for (int l = 0; l < num_of_hash; l++){
        for (int i = 0; i < vm; i++){
            for(int s=1;s<=malti;s++){
                fx[l][i][s] = minhash[l][i+(vm*(s-1))];//アルファベットに対してs番目の割り当て値
            }
        }
    }
    
    ////////////////////////////////////////////////////////////////
   
    int maxcount=0; //残っている要素の数
    /////////////////////////////////////////////////////////
    /*クエリのハッシュ値の計算*/
    for (int l = 0; l < num_of_hash; l++)
    {
        val = hashvalue(minhash[l],queri);
        hashval.push_back(val);//現時刻のハッシュ値
    }
    int tmp;
    //ここから時刻による更新
    // int out;
    int second;
    // cout<<t<<"AAA"<<"\n";
    int outcount=0;
    int incount=0;
    clock_t start = clock();//ここから時間を測定
    while(t < dmax)
    {    for(int i = 0;i < r; i++)
        {
            list[i].sim = 0;
        }
        
        for(int i=0;i<r;i++){
            //出ていく処理
            if (t >= 100){
                int out=dt[i][0];
                dt[i].erase(dt[i].begin());
                histgram[i][out]--;
              /*  for(int l=0;l<num_of_hash;l++){
                    if (out==minimum_of_allocation[i][l][0].label){
                        outcount++;
                        minimum_of_allocation[i][l][0].min = 1000000;//最小値リセット
                        for(int m=0;m<vm;m++){
                            if(histgram[i][m]!=0){
                                for(int n=1;n<=histgram[i][m];n++){
                                    int hist_min = fx[l][m][n];
                                    if(minimum_of_allocation[i][l][0].min>hist_min){//最小値の更新
                                        minimum_of_allocation[i][l][0].min=hist_min;
                                        minimum_of_allocation[i][l][0].label=m;
                                    }
                                }
                            }
                        }
                    }
                }*/
            }
            //入ってくる処理
            int In; //データストリームに入ってくる一番新しい要素
            In=database[i][t];
            dt[i].push_back(In);
            histgram[i][In]++;
          //  int h_number = histgram[i][In];
            
            for(int l=0;l<num_of_hash;l++){
               // int In_value = fx[l][In][h_number];
                vector<int> check(500,0);
            //    minimum_of_allocation[i][l].min = 1000000;//最小値リセット
                int min = 10000;
                int label = 1;
                for(int x=0;x<dt[i].size();x++){
                    int x_label = dt[i][x];
                    if(check[x_label] == 0){
                        check[x_label]=1;
                        int h_number = histgram[i][x_label];
                        for(int y=1;y<=h_number;y++){
                            int x_val = fx[l][x_label][y];
                            if(min>x_val){
                                min=x_val;
                                label=x_label;
                            }
                        }
                    }
                }
                minimum_of_allocation[i][l].min = min;
                minimum_of_allocation[i][l].label = label;
                
                
              /*  if(minimum_of_allocation[i][l][0].min>In_value){//最小値の更新
                    incount++;
                    minimum_of_allocation[i][l][0].min=In_value;
                    minimum_of_allocation[i][l][0].label=In;
                }*/
                
                
                
                if (t >= 99){
                    if (t == 111 && i == 260 && l==99){
                     //   cout<<hashval[l]<<" "<<minimum_of_allocation[i][l][0].min<<" ";
                    }
                    if(hashval[l]==minimum_of_allocation[i][l].min){
                        list[i].sim++;
                    }
                }
            }
        }
        
        
        
        
        ///////////////////////////////
        /*全集合をminヒープに挿入*/
        if (t >= 99){
            for(int i = 0;i < r; i++)
            {
                if(i < k)//k番目までのデータはそのままminヒープに挿入
                {
                    v.push(list[i]);
                }
                else//k番目以降のデータはrootより大きければminヒープに挿入
                {
                    if(v.top().sim < list[i].sim)
                    {
                        v.pop();
                        v.push(list[i]);
                    }
                }
            }
            /*top-kを出力*/
            for(int i=0;i<k;i++)
            {
                tmp = v.top().id;
                if(t==400){
                    cout << list[tmp].sim << " ";
                    //	cout <<tmp<< " ";
                    if(i==k-1){
                      //  cout<< "\n";
                        // cout<<list[3].sim<<" "<<list[637].sim <<"\n";
                    }
                }
                v.pop();
            }
        }
        if (t >= 350 && t <400){
         cout<<t<<" "<<list[9].sim<<"\n";
         }

        t++;
    }
     cout<<"\n";
    cout<<"out: "<<outcount<<"\n";
    cout<<"in: "<<incount<<"\n";
    clock_t end = clock();//ここまで時間測定
    char* rfile = argv[7];//結果出力ファイル
    ofstream fout(rfile,ios::app);
    fout << (double)(end - start)/CLOCKS_PER_SEC << endl;
    return 0;
}

