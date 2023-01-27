class CountMinSketch {
  // array of hash values for a particular item
  // contains two element arrays {aj,bj}
  int **hashes;
  unsigned int c1, c2;
  // array of arrays of counters
  int **countMinSketchTable;
  // vector<vector<int>> countMinSketchTable;

 public:
  CountMinSketch(int c1, int c2);

  int get_freq(int j);
  void update(int j, int c);
  // generate "new" aj,bj
  void genajbj(int **hashes, int i);

  // destructor
  ~CountMinSketch();
};

int get_freq(CountMinSketch *CountMinSketch, int j);

void update(CountMinSketch *CountMinSketch, int j, int value);
