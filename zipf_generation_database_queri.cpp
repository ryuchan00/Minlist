////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ./zipf  ウィンドウサイズ databaseのdata数 マルチセットの要素の数の上限 要素の種類  alpha//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<random>
#include <assert.h>             // Needed for assert() macro
#include <stdio.h>              // Needed for printf()
#include <stdlib.h>             // Needed for exit() and ato*()
#include <math.h>               // Needed for pow()
#include <queue>
//----- Constants -----------------------------------------------------------
#define  FALSE          0       // Boolean false
#define  TRUE           1       // Boolean true
#define PERIOD     100000      //データストリームの長さ
//----- Function prototypes -------------------------------------------------
int      zipf(double alpha, int n);  // Returns a Zipf random variable
double   rand_val(int seed);         // Jain's RNG
void     mergeSort(std::vector<int> arr[], int l, int r);
void     merge(std::vector<int> arr[], int l, int m, int r);
void     merge_sort (std::vector<int> array[], int left, int right);

void merge_sort (std::vector<int>& array, int left, int right) {
    int i, j, k, mid;
    std::vector<int> work(right+1,0);  // 作業用配列
    if (left < right) {
        mid = (left + right)/2; // 真ん中
        merge_sort(array, left, mid);  // 左を整列
        merge_sort(array, mid+1, right);  // 右を整列
        for (i = mid; i >= left; i--) { work[i] = array[i]; } // 左半分
        for (j = mid+1; j <= right; j++) {
            work[right-(j-(mid+1))] = array[j]; // 右半分を逆順
        }
        i = left; j = right;
        for (k = left; k <= right; k++) {
            if (work[i] < work[j]) { array[k] = work[i++]; }
            else                   { array[k] = work[j--]; }
        }
    }
}


double rand_val(int seed)
{
    const long  a =      16807;  // Multiplier
    const long  m = 2147483647;  // Modulus
    const long  q =     127773;  // m div a
    const long  r =       2836;  // m mod a
    static long x = rand();               // Random int value
    long        x_div_q;         // x divided by q
    long        x_mod_q;         // x modulo q
    long        x_new;           // New x value
    // Set the seed if argument is non-zero and then return zero
    if (seed > 0)
    {
        x = seed;
        return(0.0);
    }
    
    // RNG using integer arithmetic
    x_div_q = x / q;
    x_mod_q = x % q;
    x_new = (a * x_mod_q) - (r * x_div_q);
    //  std::cout<< x_new<<"\n";
    if (x_new > 0)
        x = x_new;
    else
        x = x_new + m;
    // Return a random value between 0.0 and 1.0
    return((double) x / m);
}
int zipf(double alpha, int n)
{
    static int first = TRUE;      // Static first time flag
    static double c = 0;          // Normalization constant
    double z;                     // Uniform random number (0 < z < 1)
    double sum_prob;              // Sum of probabilities
    double zipf_value;            // Computed exponential value to be returned
    int    i;                     // Loop counter
    
    // Compute normalization constant on first call only
    if (first == TRUE)
    {
        for (i=1; i<=n; i++)
        c = c + (1.0 / pow((double) i, alpha));
        c = 1.0 / c;
        
        first = FALSE;
    }
    // Pull a uniform random number (0 < z < 1)
    do
    {
        z = rand_val(0);
        
    }
    while ((z == 0) || (z == 1));
    
    // Map z to the value
    sum_prob = 0;
    
    for (i=1; i<=n; i++)
    {
        sum_prob = sum_prob + c / pow((double) i, alpha);
        if (sum_prob >= z)
        {
            zipf_value = i;
            break;
        }
    }
    
    // Assert that zipf_value is between 1 and N
    assert((zipf_value >=1) && (zipf_value <= n));
    
    return(zipf_value);
}
void vprint(std::vector<int> &hist, int N_elements)
{
    std::priority_queue<int> v;
    for(int l=0;l<N_elements;l++){
        if(l < 10)//top-kのk
        {
            v.push(hist[l]);//大きい順
        }
        else
        {
            if(v.top() < hist[l])
            {
                v.pop();
                v.push(hist[l]);
            }
        }
    }
    while (!v.empty()) {
       std::cout << v.top() << std::endl;
       v.pop();
     }
}

int main(int argc,char* argv[])
{	
    int w = atoi(argv[1]); //window size
    int dbsize = atoi(argv[2]); //databaseのdata数
    int malti = atoi(argv[3]);
    int N_elements = atoi(argv[4]); //集合の要素数
    double alpha = atof(argv[5]); //偏り
    std::ofstream ofs("zipf_database.txt");
    //std::vector< std::vector<int> > hist(dbsize);
    std::vector<std::vector<int> > dt(dbsize);
    
    //std::vector<int> aaa(4000);
    
    
    //for(int i=0;i<4000;i++){ aaa[i]=0;}
    //for(int l=0;l<dbsize;l++){hist[l]=aaa;}
    std::vector<int> hist(N_elements, 0);
    
    srand((unsigned int)time(NULL));
    for(int i = 0;i < dbsize; i++)
    {
        int k = 0;
        //	int abc = N_elements + 1;
        //  std::cout<< "yes"<<"\n";
        while(k < w + PERIOD)
        {
            //int l = rand()%N_elements;
            int l = zipf(alpha, N_elements) - 1;
            hist[l]++;
            
            /* if(dt[i].size()>100){
             int ccc=dt[i][0];
             hist[i][ccc]--;
             dt[i].erase(dt[i].begin());
             }
             
             if(hist[i][l]==malti+1){
             dt[i].push_back(abc);
             ofs << abc;
             hist[i][l]--;
             abc++;
             }*/
            
            //else {
            dt[i].push_back(l);
            ofs << l;
            //}
            
            /*  if(hist[i][database[l][j]]==6){
             std::cout<< "yes"<<"\n";
             }*/
            if (k < w + PERIOD-1){
                ofs<< ",";
            }
            k++;
            
            
        }
        ofs << "" << std::endl;
    }
    
    vprint(hist,N_elements);
    
    merge_sort(hist, 0, N_elements - 1);
  /*  for(int m=hist.size(); m>hist.size()-10;m--){
        std::cout<<hist[m]<<"\n";
    }*/
    // std::cout<<hist[0]<<"\n";
    
    std::ofstream ofs2("zipf_queri.txt");
    
    int queri_size = w;
    for(int j = 0; j < queri_size; j++)
    {
        
        int i=rand()%N_elements;
        ofs2 << i;
        if(j != w - 1)
        {
            ofs2<< ",";
        }
    }
    ofs2 << "" << std::endl;
    return 0;
}
