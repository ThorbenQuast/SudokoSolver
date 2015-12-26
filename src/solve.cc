#include <iostream>
#include "base.h"
#include "solve.h"
#include "parse.h"
#include "string.h"

using namespace std;
typedef std::vector<possibleEntry> possibleEntries;

int solveStepCounter = 0;
int maxGuessDepth = 3;

//shall return true when done
bool solveStep(field _field, int guessCounter) {
	if (zerocheck(_field) && checkField(_field)) {
		cout<<"SOLVED!!!"<<endl;cout<<endl;
		_field.show(guessCounter);
		return true;
	}
	if (!checkField(_field)) {
		printIndent(guessCounter);
		cout<<"Wrong placement-->revert"<<endl;cout<<endl;
		return false;
	}

	possibleEntries pEs = getPossibles(_field, guessCounter);
	if (guessCounter > maxGuessDepth) {
		printIndent(guessCounter);
		cout<<"Maximum guess depth has been reached! --> End branch"<<endl;
		return false;
	}
	if (pEs.size() == 0) {
		printIndent(guessCounter);
		cout<<"No further possibilities-->revert"<<endl;
		return false;
	}

	for (int i=0; i<pEs.size(); i++) {
		printIndent(guessCounter);
		cout<<"Step "<<++solveStepCounter<<": Setting "<<pEs[i].content<<" in field ("<<pEs[i].i<<"|"<<pEs[i].j<<") with logic '"<<pEs[i].method<<"'"<<endl;
		field tmpField = _field;
		tmpField.set(pEs[i].i, pEs[i].j, pEs[i].content);
		//tmpField.show(guessCounter);

		if(solveStep(tmpField, guessCounter)) 
			return true;
	}
}

possibleEntries getPossibles(field &Feld, int &guessCounter) {
	lineinfo line(false);   lineinfo column(true);   boxinfo box;  puzzleelement element[9][9];
	//Ablauf der Lösungsalgorithmen (1. der Einfache (löste einfache Rätsel) 2. der etwas intelligentere
	
	possibleEntries pEs;

	for(int i=0; i<9; i++) { 
		for(int j=0; j<9; j++){ 
			if(!Feld.get(i,j)){

				column.update(Feld, j);
				line.update(Feld, i);
				box.update(Feld, i, j);
				element[i][j].update(line, column, box);

				possibleEntry tbr;

				//Lösungsroutine f. einfache Rätsel
				if(element[i][j].uni()){ 
					tbr.i = i;
					tbr.j = j;
					tbr.content = element[i][j].uniset();
					tbr.method = "Unique method";
					pEs.push_back(tbr);
					return pEs;
				}

				//Lösungsroutine f. mittelschwere Rätsel
				for(int k=1; k<=9; k++){
					if(element[i][j].isPossible(k)){  
						if(lincheck(Feld, line,i,j,k)) {
							tbr.i = i;
							tbr.j = j;
							tbr.content = k;
							tbr.method = "Line check";
							pEs.push_back(tbr);
							return pEs;
						}
						if(colcheck(Feld, column,i, j, k)) {
							tbr.i = i;
							tbr.j = j;
							tbr.content = k;
							tbr.method = "Column Check";
							pEs.push_back(tbr);
							return pEs;
						}
						if(boxcheck(Feld, line, column, box, i, j, k)) {
							tbr.i = i;
							tbr.j = j;
							tbr.content = k;
							tbr.method = "Box check";
							pEs.push_back(tbr);
							return pEs;
						}
					}
				}
			}
		}
	}
	//3. If nothing has worked: guess everything
	guessCounter++;
	for(int i=0; i<9; i++) { 
		for(int j=0; j<9; j++) { 
			for (int k=1; k<=9; k++) {
				if (element[i][j].isPossible(k)) {
					possibleEntry tbr;
					tbr.i = i;
					tbr.j = j;
					tbr.content = k;
					tbr.method = "Smart guess (level "+std::to_string(guessCounter)+")";
					pEs.push_back(tbr);
				}
			}
		}
	}
	return pEs;
}

bool boxcheck(field &f, lineinfo &line, lineinfo &column, boxinfo &box, int ik,int jk, int d) {
	int i, j; i=0;j=0; 
	if(ik>=3&&ik<6) 
		i=3; 
	else if(ik>=6&&ik<9) 
		i=6;
	if(jk>=3&&jk<6) 
		j=3; 
	else if(jk>=6&&jk<9) 
		j=6;
	int ilim=i+3; 
	int jlim=j+3;

	while(i<ilim) {
		for(int jhelp=j; jhelp<jlim; jhelp++) { 
			if(i==ik&&jhelp==jk)
				continue;
			if(!(f.get(i,jhelp))) {
				box.update(f,i,jhelp);line.update(f, i);column.update(f,jhelp);
				if(box.isPossible(d)&&column.isPossible(d)&&line.isPossible(d)) 
					return false;
			}
		}
		i++;
	}
	return true;
}          

bool lincheck(field &f, lineinfo &line, int i,int j, int d) {    
	for(int k=0; k<9; k++) {
		if(k!=i && !(f.get(k,j))) { 
			line.update(f,k); 
			if(line.isPossible(d)) {
				return false;
			} 
		}
	}
	return true;
}

bool colcheck(field &f, lineinfo &column, int i,int j, int d){    
	for(int k=0; k<9; k++) {
		if(k!=j && !(f.get(i,k))){ 
			column.update(f,k); 
			if(column.isPossible(d)) {
				return false;
			}
		}
	}
	return true;
}