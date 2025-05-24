#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include "animeTraits.h"
#include "readCsv.h"
#include "BDT.h"
using namespace std;

 void learnNewCharacter(){
 	string id,name,gender,hairColor;
 	  string FN= "anime.csv";
    ofstream write(FN, ios::app); 

    if (!write.is_open()) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }
 	
 	int tagsCount,animeCount,mangaCount;
 	
 	
 	cout<<"Enter Name of the character: ";
 	cin>>name;
 	
 	cout<<"Enter Hair Color of the character: ";
 	cin>>hairColor;
 	
 	cout<<"Enter Gender of the character: ";
 	cin>>gender;
 	
 	cout<<"How many tags it have?: ";
 	cin>>tagsCount;
 	string tags[tagsCount];
 	
 	for (int i=0;i<tagsCount;i++){
 		cout<<"Enter Tags: "<<i;
 		cin>>tags[i];
	 }
	 
	cout<<"How many anime it have?: ";
 	cin>>animeCount;
 	string anime[animeCount];
 	
 	for (int i=0;i<tagsCount;i++){
 		cout<<"Enter Anime: "<<i;
 		cin>>anime[i];
	 }
	 
	 
	cout<<"How many Manga it have?: ";
 	cin>>mangaCount;
 	string manga[mangaCount];
 	
 	for (int i=0;i<tagsCount;i++){
 		cout<<"Enter Manga: "<<i;
 		cin>>manga[i];
 		
	 }
	 
 	  write.close();
 	
 }

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
