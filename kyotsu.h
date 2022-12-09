#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
#include <vector>
/*データベース読み込み*/
std::vector<std::vector<int> > readdatabase(char* filename) {
  int i = 0;
  std::vector<std::vector<int> > database;
  std::ifstream ifs(filename);
  std::vector<int> empty;
  std::string str, x;
  while (getline(ifs, str)) {
    std::istringstream line(str);
    database.push_back(empty);
    while (getline(line, x, ',')) {
      database[i].push_back(atoi(x.c_str()));
    }
    i++;
  }
  return database;
}
//データベースは
// 1,2,3
// 4,5,6
//のようにカンマで区切られている

/*データベース読み込み*/
std::vector<int> readdatabase_line(char* filename) {
  std::ifstream ifs(filename);
  std::vector<int> database;
  std::string str, x;
  getline(ifs, str);
  std::istringstream line(str);
  while (getline(line, x, ',')) {
    database.push_back(atoi(x.c_str()));
  }
  return database;
}

/*1行ずつデータベース読み込み*/
std::vector<int> portion_readdatabase(char* filename, int read_limit) {
  std::ifstream ifs(filename);
  std::vector<int> database;
  std::string str, x;
  getline(ifs, str);
  std::istringstream line(str);
  while (getline(line, x, ',')) {
    database.push_back(atoi(x.c_str()));
  }
  return database;
}

/*ストリームの読み込み*/
std::vector<int> readqueri(char* filename) {
  std::ifstream ifs(filename);
  std::vector<int> queri;
  std::string str, x;
  getline(ifs, str);
  std::istringstream line(str);
  while (getline(line, x, ',')) {
    queri.push_back(atoi(x.c_str()));
  }
  return queri;
}
//ストリームは
// 1,2,3,4,5,6
//のようにカンマ区切り、改行なし

/*Q0の作成*/
std::vector<int> make_q0(int w, std::vector<int>& queri) /* w: ウインドウサイズ queri:クエリを表すvector*/
{
  std::vector<int> qt;
  qt.push_back(0);
  for (int i = 0; i < w; i++) {
    qt.push_back(queri[i]);
  }
  return qt;
}

/*d0の作成*/
std::deque<std::deque<int> > make_d0(int w, std::vector<std::vector<int> >& database, int r)
/* w: ウインドウサイズ database:データベースを表すvector r:データ数*/
{
  std::deque<std::deque<int> > dt(r);
  for (int j = 0; j < r; j++) {
    // dt[j][0]=0;
    dt[j].push_back(0);
    for (int i = 0; i < w; i++) {
      // dt[j][i]=database[j][i];
      dt[j].push_back(database[j][i]);
    }
  }
  return dt;
}

/*データ出力*/
template <class X>
void printdata(const std::vector<X> V) {
  for (int i = 0; i < V.size(); i++) {
    std::cout << V[i] << " ";
  }
  std::cout << " " << std::endl;
}
