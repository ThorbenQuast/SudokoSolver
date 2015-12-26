#include <string>

bool lincheck(field &f, lineinfo &line, int i,int j, int d);    
bool colcheck(field &f,lineinfo &column, int i,int j, int d);  
bool boxcheck(field &f, lineinfo &line, lineinfo &column, boxinfo &box, int ik,int jk, int d); 

struct possibleEntry{
	int i;
	int j;
	int content;
	std::string method;
};

typedef std::vector<possibleEntry> possibleEntries;
bool solveStep(field _field, int guessCounter);
possibleEntries getPossibles(field &Feld, int &guessCounter);