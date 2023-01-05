/*Minhash読み込み*/
std::vector< std::vector<int> > readminhash(char* filename)
{
	int i = 0;
	std::vector< std::vector<int> > minhash;
	std::ifstream ifs(filename);
	int line = 0;
	std::vector<int> empty;
	std::string str,x;
	while(getline(ifs,str))
	{
		std::istringstream line(str);
		minhash.push_back(empty);
		while(getline(line,x,','))
		{
			minhash[i].push_back(atoi(x.c_str()));
		}
		i++;
	}
	return minhash;
}

/*ハッシュ値の計算*/
int hashvalue(std::vector<int> &hash,std::vector<int> &data)
{
    	int value = hash.size() + 1;
	for(int i = 0;i < data.size();i++)
	{
		if (value > hash[data[i]])
        	{
            		value = hash[data[i]];
        	}
	}
    	return value;
}

/*
struct rank
{
	int id;
	int sim;
	bool operator<(const rank& rhs) const
    	{
		return sim > rhs.sim;
    	}
	};*/
//jac.hとほぼ同じ。
//simがintになっているのは、
//ハッシュの衝突回数で類似度
//を近似してるから
