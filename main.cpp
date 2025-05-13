#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include "animeTraits.h"
#include "readCsv.h"
#include "BDT.h";
using namespace std;

int main() {
	vector<AnimeTraits> animeList;
	ReadCSV r;
    r.readData(animeList);

    BDT tree(animeList);
    tree.buildTree();
    
    while(true){
    	  tree.guessCharacter();
    	  string a;
    	  cout<<"Play again (yes/no) :";
    	  cin>>a;
    	  if(a=="no") {
    	  	break;
		  };
	}
  
  
    
  //  tree.builtQuestions();
   
 
}
