struct contents{
    int label;
    int value;
    int time;
    int multiplicity;   // 入ってきたときの多重度
};

struct ranking
{
    int id;
    int sim;
    bool operator<(const ranking& rhs) const
    {
        return sim > rhs.sim;
    }
};

struct index {
  int multiplicity;
  int value;
};