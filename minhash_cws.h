/*Minhash読み込み*/
std::vector<std::vector<int> > readminhash(char *filename) {
  int i = 0;
  std::vector<std::vector<int> > minhash;
  std::ifstream ifs(filename);
  int line = 0;
  std::vector<int> empty;
  std::string str, x;
  while (getline(ifs, str)) {
    std::istringstream line(str);
    minhash.push_back(empty);
    while (getline(line, x, ',')) {
      minhash[i].push_back(atoi(x.c_str()));
    }
    i++;
  }
  return minhash;
}
