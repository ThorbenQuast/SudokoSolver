#include <fstream>
#include <vector>

//Datentypen
class field{
  private:
    int** element;
    int dim;
  
  public:
    field(char* input, int dim);       
    ~field();
    field(const field &other);
    const field &operator=(const field &other);

    void show(int indentLevel);
    int get(int i, int j);
    void set(int i, int j, int d);
};


class lineinfo{
  private:
    std::vector<int> _possibles;
    bool _unique;
    bool _isColumn;

  public:
    lineinfo(bool isColumn);
    ~lineinfo();

    void update(field &t,int i, int skip_i = -1);
    bool isPossible(int test);
};


class boxinfo{
  private: 
    std::vector<int> _possibles;
    bool _unique;

    std::vector<int> restricted;
  public:
    boxinfo();
    ~boxinfo();

    void update(field &t, int ik, int jk, bool skip = false);
    bool isPossible(int test);
};

class puzzleelement{
  private: 
    std::vector<int> _possibles;
    bool _unique;

  public:
    puzzleelement();
    ~puzzleelement();

    void update(lineinfo &l, lineinfo &c, boxinfo &b);
    bool uni();
    int uniset();
    bool isPossible(int d);
};

//parts for medium hard sudoku's 
bool lincheck(field &f, lineinfo &line, int i,int j, int d);          
bool lincheck(field &f, lineinfo &line, int i,int j, int d);
bool colcheck(field &f, lineinfo &column, int i,int j, int d);
bool colcheck(field &f,lineinfo &column, int i,int j, int d);
bool boxcheck(field &f, lineinfo &line, lineinfo &column, boxinfo &box, int ik,int jk, int d); 
bool setsmart(int i, int j, puzzleelement &element, field &f, lineinfo &line, lineinfo &column, boxinfo &box);
bool boxcheck(field &f, lineinfo &line, lineinfo &column, boxinfo &box, int ik,int jk, int d);         
bool colcheck(field &f, lineinfo &column, int i,int j, int d);

void printIndent(int level);
