#pragma once
#include<iostream>
using namespace std;
#include "animeTraits.h"
#include<vector>
#include <set>
#include <unordered_map>
#include <cmath>
class Node{
	public:
		string criteria;
		Node *yes;
		Node *no;
		string data;
	//	bool isQuestion;
		vector<AnimeTraits> characters;
		
		Node(string criteria,string data){
	//		isQuestion=false;
			this->data=data;
			yes=no=nullptr;
			this->criteria=criteria;
		
		}
};


class BDT{
	vector<string>attributeNames;
	vector<string>attributeTypes;
	vector<string>attributeValues;
	public:
		Node *root;
		vector<AnimeTraits> characters;
		
		BDT(vector<AnimeTraits> characters){
			this->characters=characters;
		}
		


    bool hasTag(AnimeTraits& c, const string& tag) {
        for (string t : c.tags) if (t == tag) return true;
        for (string a : c.anime) if (a == tag) return true;
        for (string m : c.manga) if (m == tag) return true;
        return false;
    }


   
    
//    vector<string> collectAllColors(vector<AnimeTraits> characters) {
//    set<string> colorSet;
//    for (AnimeTraits& c : characters) {
//        if (!c.hairColor.empty()) {
//            colorSet.insert(c.hairColor);
//        }
//    }
//
//    return vector<string>(colorSet.begin(), colorSet.end());
//}

vector<string> collectAllColors(vector<AnimeTraits> characters) {
        vector<string> all;
        
        for (AnimeTraits  c : characters) {
        	bool found=false;
        	for(string a:all){
        		if(a==c.hairColor|| c.hairColor==""){
        			found=true;
        			break;
				}
			}
			
			if(!found){
				all.push_back(c.hairColor);
			}
        
        }
        return all;
    }



//     vector<string> collectAllTags(vector<AnimeTraits> characters) {
//         set<string> uniqueTags;
//     for (const AnimeTraits& c : characters) {
//        for (string tag : c.tags)   if (!tag.empty()) uniqueTags.insert(tag);
//        for (string anime : c.anime) if (!anime.empty()) uniqueTags.insert(anime);
//        for (string manga : c.manga) if (!manga.empty()) uniqueTags.insert(manga);
//    }
//    
//    return vector<string>(uniqueTags.begin(), uniqueTags.end());
//}

 vector<string> collectAllTags(vector<AnimeTraits> characters) {
        vector<string> all;
        for (AnimeTraits  c : characters) {
            addUnique(all, c.tags);
           // addUnique(all, c.anime);
           // addUnique(all, c.manga);
        }
        return all;
    }



  // generate unique tags
  void addUnique(vector<string>& to, vector<string> from) {
    for (string item : from) {
        bool found = false;
        for (string c : to) {
            if (c == item || item=="") {
                found = true;
                break; 
            }
        }
        if (!found) {
            to.push_back(item);
        }
    }
}


 



void builtQuestions(){
    attributeNames .push_back("gender=Female?");
    attributeTypes .push_back("gender");
	attributeValues.push_back("Female");

	attributeNames .push_back("gender=Male?");
	attributeTypes .push_back("gender");
	attributeValues.push_back("Male");
	
	attributeNames .push_back("gender=Other?");
	attributeTypes .push_back("gender");
	attributeValues.push_back("");
	
	
	vector<string> hairColors = collectAllColors(characters);
		cout<<"Color size: "<<hairColors.size()<<endl;
	 for(string color: hairColors){
	 
       attributeNames .push_back("hairColor=" + color + "?");
       attributeTypes .push_back("hairColor");
       attributeValues.push_back(color);
	 }
	 vector<string> tags=collectAllTags(characters);
	 cout<<"Tags Size: "<<tags.size()<<endl;
	 for(string tag:tags){
	 	attributeNames .push_back("hasTag=" + tag + "?");
        attributeTypes .push_back("tag");
        attributeValues.push_back(tag);	
	 }	
}
 
// returns true if character `c` satisfies question `idx`
bool testAttribute(int idx, AnimeTraits c) {
     string type  = attributeTypes [idx];
     string value = attributeValues[idx];

    if (type == "gender") {
        return c.gender == value;
    }
    else if (type == "hairColor") {
        return c.hairColor == value;
    }
    else if (type == "tag") {

        return hasTag(c, value);
    }
    
    return false;
}

double entropy(const vector<AnimeTraits>& chars) {
    // Empty or singleton sets have zero entropy
    if (chars.size() <= 1) {
        return 0.0;
    }

    // 1) Count how many times each name appears
    unordered_map<string,int> freq;
    for (const auto& c : chars) {
        freq[c.name]++;
    }

    // 2) Compute –∑ pᵢ·log₂(pᵢ)
    double H = 0.0;
    double N = static_cast<double>(chars.size());
    for (const auto& kv : freq) {
        double p = kv.second / N;    // probability of this class
        H     -= p * log2(p);        // add –p·log₂(p)
    }

    return H;
}

double infoGain( vector<AnimeTraits>& allChars, int attrIdx) {
                 vector<AnimeTraits> yesSet,noSet;
                 
              for (AnimeTraits c : allChars) {
              	
              if (testAttribute(attrIdx, c)) yesSet.push_back(c);
              else  noSet.push_back(c);
  				  }
  				  
    double H0 = entropy(allChars);
    double H1 = entropy(yesSet);
    double H2 = entropy(noSet);
    double p1 = (double)yesSet.size() / allChars.size();
    return H0 - (p1*H1 + (1-p1)*H2);	  
  				  	  
		}
		
		Node* buildNode(
    vector<AnimeTraits> allChars,
    vector<string>& attributeNames,
    vector<string>& attributeTypes,
    vector<string>& attributeValues
) {
    // 1) STOP: exactly one character
    if (allChars.size() == 1) {
        Node* leaf = new Node("LEAF", "");
        leaf->characters = allChars;
        return leaf;
    }
    // 2) STOP: no more questions
    if (attributeNames.empty()) {
        Node* leaf = new Node("LEAF", "");
        leaf->characters = allChars;
        return leaf;
    }

    // 3) Find best question by max infoGain
    double bestGain = -1;
    int   bestIdx  = -1;
    for (int i = 0; i < attributeNames.size(); ++i) {
        double gain = infoGain(allChars, i);
        if (gain > bestGain) {
            bestGain = gain;
            bestIdx  = i;
        }
    }

    // 4) If no split helps, make a leaf
    if (bestGain <= 0) {
        Node* leaf = new Node("LEAF", "");
        leaf->characters = allChars;
        return leaf;
    }

    // 5) Otherwise, split on bestIdx
    vector<AnimeTraits> yesSet, noSet;
    for (auto& c : allChars) {
        if (testAttribute(bestIdx, c)) yesSet.push_back(c);
        else                            noSet.push_back(c);
    }

    // 6) Grab the question text/type/value
    string questionText = attributeNames[bestIdx];
    string questionType = attributeTypes[bestIdx];

    // 7) Remove the used question from our pools
    attributeNames .erase(attributeNames .begin() + bestIdx);
    attributeTypes .erase(attributeTypes .begin() + bestIdx);
    attributeValues.erase(attributeValues.begin() + bestIdx);

    // 8) Create node & recurse
    Node* node = new Node(questionType, questionText);
    node->yes = buildNode(yesSet, attributeNames, attributeTypes, attributeValues);
    node->no  = buildNode(noSet,  attributeNames, attributeTypes, attributeValues);
    return node;
}


    void buildTree() {
        // 1) fill the parallel vectors
        builtQuestions();
        // make local copies so recursion can erase them
        vector<string> names  = attributeNames;
        vector<string> types  = attributeTypes;
        vector<string> values = attributeValues;

        root = buildNode(characters, names, types, values);
    }
    
        void guessCharacter() {
        Node* cur = root;
        while (cur && cur->criteria != "LEAF") {
            cout << cur->data<< " (yes/no): ";
            string ans; cin >> ans;
            cur = (ans=="yes" ? cur->yes : cur->no);
        }
        if (cur->characters.size() == 1){
        	   cout<<cur->characters[0].name<<endl;
        	   return ;
            
		}
            
        throw runtime_error("Could not narrow to a single character");
    }
		
		
		
		
		
};





