#include <iostream>
#include "base.h"

#include "parse.h"

bool zerocheck(field &t){
	for(int i=0; i<9; i++) 
		for (int j=0; j<9; j++)
			if(!t.get(i,j)) 
				return false; 
	return true;
}


bool parse(char* input){
	std::fstream f; 
	f.open(input);
	int d, c; 
	d = c = 0;
	while(!f.eof())	{
		f>>d; 
		c++; 
		if(d<0||d>9) {
			return false;
		}
	}
	f.close();
	if(c!= 81) {
		return false;
	}
	return true;
}

bool checkField(field &f){
	lineinfo line(false);
	lineinfo column(true);
	boxinfo box;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++){
			line.update(f, i, j);
			column.update(f, j, i);
			box.update(f, i, j, true);
			int el = f.get(i,j);
			if (el == 0)
				continue;
			if (!line.isPossible(el) || !column.isPossible(el) || !box.isPossible(el)){
				return false;
			}
		}
	return true;
}

