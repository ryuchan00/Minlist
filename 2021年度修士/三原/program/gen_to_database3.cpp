///////////////////////////////////////////////////////////////////////////////////////////////////////
// ./gen_to_database3 元データのファイル名 ウィンドウサイズ databaseのdata数 マルチセットの要素の数の上限//
// 元データの要素をランダムに組み合わせてデータベースを作る関数                                         //
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<random>
#define PERIOD     100000  //データストリームの長さ
#define MAX_ELEMENT (300)
int main(int argc,char* argv[])
{
        char* fname = argv[1]; //データファイル
	std::ifstream ifs(fname);
	int a,number = -1;
	std::vector< std::vector<int> > database;
	std::vector<int> em;

	int w = atoi(argv[2]); //window size
	int dbsize = atoi(argv[3]); //databaseのdata数
	int k = 0;
	
	int z = 0;
	int t = 0;
	int x;
	while(1)
	{
		if(z == 0)
		{
			ifs >> z;
			if(number > 0)
			{
				if(database[number] == em)
				{
					break;
				}
			}
			database.push_back(em);
			number++;
			t++;
		}
		else
		{
			ifs >> x;
			database[number].push_back(x);
			z--;
		}
	}


	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> rand100(0,number); //rand100(mt)
	std::vector< std::vector<int> > hist(dbsize);
	std::vector<std::vector<int> > dt(dbsize);
	int malti=atoi(argv[4]); //マルチセットの上限
	int line = atoi(argv[5]);
	std::vector<int> aaa(line);
	//	for(int l=0;l<dbsize;l++){ dt[l]=aaa; }
	
	for(int i=0;i<line;i++){ aaa[i]=0;}
	for(int l=0;l<dbsize;l++){
	  hist[l]=aaa;
	  // dt[l].push_back(0);
	}
	
	std::ofstream ofs("database.txt");

	for(int i = 0;i < dbsize; i++)
	{
	  k = 0;
	  int abc = MAX_ELEMENT + 1;
	  while(k < w + PERIOD)
	    {
	      if (k > 0)
		{
		  ofs<< ",";
		}
	      // int l = rand100(mt);
	      int l=rand()%line;

	      //   int abc=301;
	      for(int j = 0;j < database[l].size();j++)
		{
		  
		  hist[i][database[l][j]]++;

        

		  if(dt[i].size()>w){
		    int ccc=dt[i][0];
		    hist[i][ccc]--;
		    dt[i].erase(dt[i].begin());
		  }
		  
		  if(hist[i][database[l][j]]==malti+1){
		    dt[i].push_back(abc);
		    ofs << abc;
		    hist[i][database[l][j]]--;
		    abc++;
		    }
		 
		  
		  else {
		    dt[i].push_back(database[l][j]);
		    ofs << database[l][j];
		  }
		  /*if(hist[i][database[l][j]]==6){
		      //  std::cout<< "yes"<<"\n";
		      }*/
		  
		    
		  if(j != database[l].size() - 1)
		    {
		      ofs<< ",";
		    }
		  k++;
		  // hist[i][database[l][j]]++;
			  

			
		}
	    }
		ofs << "" << std::endl;
	}

	/*	std::ofstream ofs2("queri.txt");
	//int i = rand100(mt);
	int i=rand()%line;
	for(int j = 0; j < database[i].size(); j++)
		{
			ofs2 << database[i][j];
            if(j != database[i].size() - 1)
			{
				ofs2<< ",";
			}
		}
	ofs2 << "" << std::endl;
	*/
	return 0;
}
