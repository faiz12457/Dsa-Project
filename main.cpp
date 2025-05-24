#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include "animeTraits.h"
#include "readCsv.h"
#include "BDT.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
	
	vector<AnimeTraits> animeList;
	ReadCSV r;
    r.readData(animeList);
    BDT tree(animeList);
    tree.builtTree();
    while(true){
    tree.playGame();
    string a;
    cout<<"Play again (yes/no): ";
    cin>>a;
    if(a=="no")break;
}

}
