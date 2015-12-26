//main
#include <iostream>
using namespace std;

#include "base.h"

#include "solve.h"
#include "parse.h"

#include "SudokuSolverConfig.h"



int main(int argc, char* argv[]){
  if (argc < 2){
    cout<<"SudokuSolver v."<<SudokuSolver_VERSION_MAJOR<<"."<<SudokuSolver_VERSION_MINOR<<endl;
    cout<<"by Thorben Quast"<<endl<<endl;
    cout<<"Correct usage: "<<endl;
    return 1;
  }
  //Datentypendeklaration und Syntax+ Zeilen/Spalten Parsing 
  if(!parse(argv[1])){ 
    cout<<"Syntax error in sudoku!"<<endl; 
    return -1;
  }
  field Feld(argv[1], 9); 

  if(!checkField(Feld)) {
    cout<<"Invalid sudoku setup!"<<endl; 
    return -1;
  }

  cout<<"Input field: "<<endl;
  Feld.show(0);
  cout<<endl<<endl;
  int guessCounter = 0;
  solveStep(Feld, guessCounter);

  return 0;
}
