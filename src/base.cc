#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "base.h"

//field components
field::field(char* input, int dim){               
  std::fstream f; 
  f.open(input);
  int entry = 0;  
  this->dim = dim;
  element = new int* [dim];
  for (int i = 0; i < dim; i++){
    element[i]=new int[dim];
    for (int j=0; j<dim; j++){
      f >> entry; 
      element[i][j] = entry;
    }
  }
}

field::field(const field &other){
  int dim = other.dim;
  this->dim = dim;
  this->element = new int* [dim];
  for (int i = 0; i < dim; i++){
    this->element[i]=new int[dim];
    for (int j=0; j<dim; j++){
      this->element[i][j] = other.element[i][j];
    }
  }
}

field::~field(){
  for(int i=0; i<dim; i++) 
    delete [] element[i]; 
  delete [] element;
}
void field::show(int indentLevel){
  for(int i=0; i<dim; i++){
    printIndent(indentLevel);
    for(int j=0; j<dim; j++){
      std::cout<<element[i][j]<<" ";
    }std::cout<<std::endl;
  }
}
int field::get(int i, int j){
  return element[i][j];
} 
void field::set(int i, int j, int d){
  element[i][j]=d;
}     


//lineinfo components
lineinfo::lineinfo(bool isColumn){
  _isColumn = isColumn;
  _possibles.reserve(9);  
  _unique=false;
}
lineinfo::~lineinfo(){
  _possibles.clear();
}
void lineinfo::update(field &t, int i, int skip_i){ 
  _possibles.clear(); 
  std::vector<int> restricted;
  restricted.reserve(9); 
  for (int j=0; j<9; j++){
    if (j == skip_i) 
      continue;
    int entry = _isColumn ? t.get(j, i): t.get(i, j);
    if(entry != 0) 
      restricted.push_back(entry);
  }
  for(int j=1; j<=9; j++){
    if(!(std::find(restricted.begin(), restricted.end(), j)!=restricted.end()))
      _possibles.push_back(j);
  }
  _unique = (_possibles.size() == 1);
}
bool lineinfo::isPossible(int test){
  return (std::find(_possibles.begin(), _possibles.end(), test)!=_possibles.end());
}
     

//continue here:
boxinfo::boxinfo(){
  _possibles.reserve(9); 
  _unique=false;
}
boxinfo::~boxinfo(){
  _possibles.clear();
}
void boxinfo::update(field &t, int ik, int jk, bool skip){    

  int i = 3* ((int) ik/3);
  int j = 3* ((int) jk/3); 
  _possibles.clear(); 
  std::vector<int> restricted;
  restricted.reserve(9); 
  for(int k = i; k < i + 3; k++){
    for(int q = j; q < j + 3; q++){
      if (skip && k == ik && q == jk) continue;
      int temp=t.get(k, q);
      if(temp!=0) 
        restricted.push_back(temp);
    }
  }
  std::vector<int>::iterator it;
  for(int j=1; j<=9; j++){
    if(!(std::find(restricted.begin(), restricted.end(), j)!=restricted.end()))
      _possibles.push_back(j);
  }
  _unique = (_possibles.size() == 1);
}
bool boxinfo::isPossible(int test){
  return (std::find(_possibles.begin(), _possibles.end(), test)!=_possibles.end());
}
 

puzzleelement::puzzleelement(){
  _unique=false; 
  _possibles.reserve(9);
}
puzzleelement::~puzzleelement(){
  _possibles.clear();
}
void puzzleelement::update(lineinfo &l, lineinfo &c, boxinfo &b){
  _unique=false; 
  _possibles.clear();
  for(int el=1; el<=9; el++)
    if(l.isPossible(el)&&c.isPossible(el)&&b.isPossible(el))
      _possibles.push_back(el);
  _unique = (_possibles.size() == 1);
}
bool puzzleelement::uni(){
  return _unique;
}
int puzzleelement::uniset(){
  return _possibles[0];
}
bool puzzleelement::isPossible(int test){
  return (std::find(_possibles.begin(), _possibles.end(), test)!=_possibles.end());
}



void printIndent(int level) {
  for (int k=0; k<level; k++) std::cout<<"         ";
}
