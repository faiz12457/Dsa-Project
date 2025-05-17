#pragma once
#include <iostream>
using namespace std;
#include "animeTraits.h"
#include <vector>
#include <set>
#include <utility>

class Node
{
public:
	Node *yes;
	Node *no;
	Node *other;
	string question;
	vector<AnimeTraits> characters;

	Node(string question, vector<AnimeTraits> characters)
	{
		this->question = question;
		yes = nullptr;
		no = nullptr;
		other = nullptr;
		this->characters = characters;
	}
};

class BDT
{
public:
	Node *root;
	vector<AnimeTraits> characters;

	BDT(vector<AnimeTraits> characters){
		this->characters = characters;
	}
	
	~BDT(){
    destroyTree(root);
  }

	bool hasTag(AnimeTraits &c, const string &tag)
	{
		for (string t : c.tags)
			if (t == tag)
				return true;
		for (string a : c.anime)
			if (a == tag)
				return true;
		for (string m : c.manga)
			if (m == tag)
				return true;
		return false;
	}

	vector<string> collectAllColors(vector<AnimeTraits> &characters)
	{
		vector<string> all;

		for (AnimeTraits c : characters)
		{
			bool found = false;
			for (string a : all)
			{
				if (a == c.hairColor)
				{
					found = true;
					break;
				}
			}

			if (!found)
			{
				all.push_back(c.hairColor);
			}
		}
		return all;
	}
	
string findCommonColor(vector<AnimeTraits> characters) {
    vector<string> uniqueColors;
    vector<int> colorCounts;

    for (const AnimeTraits& c : characters) {
        string color = c.hairColor;
        bool found = false;

        for (int i = 0; i < uniqueColors.size(); ++i) {
            if (uniqueColors[i] == color) {
                colorCounts[i]++;
                found = true;
                break;
            }
        }

        if (!found) {
            uniqueColors.push_back(color);
            colorCounts.push_back(1);
        }
    }

    // Find color with max count
    int maxIndex = 0;
    for (int i = 1; i < colorCounts.size(); ++i) {
        if (colorCounts[i] > colorCounts[maxIndex]) {
            maxIndex = i;
        }
    }

    return  uniqueColors[maxIndex];
}

	void builtTree()
	{

		vector<AnimeTraits> yesGroup, noGroup;

		for (AnimeTraits &c : characters)
		{
			if (c.anime.size() == 0 and c.manga.size() == 0 and c.tags.size() > 0)
			{
				yesGroup.push_back(c);
			}

			//  else if(c.anime.size()>0 or c.manga.size()>0 or c.tags.size()>0){
			//  	noGroup.push_back(c);
			//  }
			else
			{
				noGroup.push_back(c);
			}
		}

		root = new Node("Does your anime only contain tags? (yes/no)", characters);
		root->yes = new Node("is your character is male (yes/no/other)", yesGroup);
		root->no = new Node("is your character have both manga and anime (yes/no) ", noGroup);

		root->yes->yes = getGenderChar(root->yes, "Male");
		root->yes->no = getGenderChar(root->yes, "Female");
		root->yes->other = getGenderChar(root->yes, "");

		vector<AnimeTraits> existInBothYes, existInBothNo;
		for (AnimeTraits &c : root->no->characters)
		{
			if (c.anime.size() > 1 and c.manga.size() > 1)
			{
				existInBothYes.push_back(c);
			}
			//              else if(c.anime.size()>1 or c.manga.size()>1){
			//              	existInBothNo.push_back(c);
			//			  }

			else
			{
				existInBothNo.push_back(c);
			}
		}

		root->no->yes = new Node("is your character is male (yes/no/other)", existInBothYes);
		root->no->no = new Node("is your character is male (yes/no/other)", existInBothNo);

		root->no->yes->yes = getGenderChar(root->no->yes, "Male");
		root->no->yes->no = getGenderChar(root->no->yes, "Female");
		root->no->yes->other = getGenderChar(root->no->yes, "");

		root->no->no->yes = getGenderChar(root->no->no, "Male");
		root->no->no->no = getGenderChar(root->no->no, "Female");
		root->no->no->other = getGenderChar(root->no->no, "");

		root->yes->yes = getHairColor(root->yes->yes, root->yes->yes->characters);
		root->yes->no = getHairColor(root->yes->no, root->yes->no->characters);
		root->yes->other = getHairColor(root->yes->other, root->yes->other->characters);

		root->no->yes->yes = getHairColor(root->no->yes->yes, root->no->yes->yes->characters);
		root->no->yes->no = getHairColor(root->no->yes->no, root->no->yes->no->characters);
		root->no->yes->other = getHairColor(root->no->yes->other, root->no->yes->other->characters);

		root->no->no->yes = getHairColor(root->no->no->yes, root->no->no->yes->characters);
		root->no->no->no = getHairColor(root->no->no->no, root->no->no->no->characters);
		root->no->no->other = getHairColor(root->no->no->other, root->no->no->other->characters);
	}

	Node *getHairColor(Node *root, vector<AnimeTraits> &characters)
	{
		string hairColors[12] = {
			"Black Hair",
			"Grey Hair",
			"Blonde Hair",
			"Brown Hair",
			"Red Hair",
			"Pink Hair",
			"White Hair",
			"Green Hair",
			"Multicolored Hair",
			"Orange Hair",
			"Purple Hair",
			"Blue Hair"};
		int size = sizeof(hairColors) / sizeof(hairColors[0]);
		vector<AnimeTraits> yesGroup, noGroup;

		for (AnimeTraits &c : characters)
		{
			if (c.hairColor == hairColors[0] ||
				c.hairColor == hairColors[1] ||
				c.hairColor == hairColors[2] ||
				c.hairColor == hairColors[3] ||
				c.hairColor == hairColors[4] ||
				c.hairColor == hairColors[5] ||
				c.hairColor == hairColors[6] ||
				c.hairColor == hairColors[7] ||
				c.hairColor == hairColors[8] ||
				c.hairColor == hairColors[9] ||
				c.hairColor == hairColors[10] ||
				c.hairColor == hairColors[11])
			{
				yesGroup.push_back(c);
			}
			else
			{
				noGroup.push_back(c);
			}
		}
		 string commonColor=yesGroup[0].hairColor;
		
        commonColor=findCommonColor (yesGroup);
        
        vector<AnimeTraits> commonColorCharYes,commonColorCharNo;
        
        for(AnimeTraits &c:yesGroup){
        	if(c.hairColor==commonColor){
        		commonColorCharYes.push_back(c);
			}
			else{
				commonColorCharNo.push_back(c);
			}
        	
		}
		vector<AnimeTraits>noHairColor,yesHairColor;
		for(AnimeTraits &c:noGroup){
			if(c.hairColor==""){
				noHairColor.push_back(c);
			}
			else{
				yesHairColor.push_back(c);
			}
		}
		
		
		root->yes = new Node("does your character have "+commonColor +" ? (yes/no)", yesGroup);
	    root->yes->yes=getTagNode(commonColorCharYes);
	
		
		
		commonColor=findCommonColor (commonColorCharNo);
		
		
	   	 commonColorCharYes.clear();
		 vector<AnimeTraits> temp;
		 temp=commonColorCharNo;
		 commonColorCharNo.clear();
		 for(AnimeTraits &c:temp){
        	if(c.hairColor==commonColor){
        		commonColorCharYes.push_back(c);
			}
			else{
				commonColorCharNo.push_back(c);
			}
        	
		}
		
		 root->yes->no=new Node("does your character have "+commonColor +" ? (yes/no)",temp);
		 root->yes->no->yes=getTagNode(commonColorCharYes);
		 
		 
		commonColor=findCommonColor (commonColorCharNo);
		commonColorCharYes.clear();
		 temp.clear();
		 temp=commonColorCharNo;
		 commonColorCharNo.clear();
		 for(AnimeTraits &c:temp){
        	if(c.hairColor==commonColor){
        		commonColorCharYes.push_back(c);
			}
			else{
				commonColorCharNo.push_back(c);
			}
        	
		}
		 	
		 	
		    root->yes->no->no=new Node("does your character have "+commonColor +" ? (yes/no)",temp);
		    root->yes->no->no->yes=getTagNode(commonColorCharYes);
		    root->yes->no->no->no=getTagNode(commonColorCharNo);

			
		root->no = new Node("does your character have hair color (yes/no)", noGroup);
    	root->no->yes=getTagNode(yesHairColor);
    	
    	
		root->no->no=getTagNode(noHairColor);
   
         
         
		return root;
	}

	Node *getGenderChar(Node *node, string gender)
	{
		vector<AnimeTraits> genderGroup;
		for (AnimeTraits c : node->characters)
		{
			if (c.gender == gender)
			{
				genderGroup.push_back(c);
			}
		}

		return new Node("Does your anime contain natural hair? (yes/no)", genderGroup);
	}
	
	
int findCommonTagSize(vector<AnimeTraits>& characters) {
	if (characters.empty()) return 0;
    vector<int> uniqueTagSizes;
    vector<int> tagCounts;

    for ( AnimeTraits& c : characters) {
        int tagSize = c.tags.size();
        bool found = false;

        for (int i = 0; i < uniqueTagSizes.size(); ++i) {
            if (uniqueTagSizes[i] == tagSize) {
                tagCounts[i]++;
                found = true;
                break;
            }
        }

        if (!found) {
            uniqueTagSizes.push_back(tagSize);
            tagCounts.push_back(1);
        }
    }

    int maxIndex = 0;
    for (int i = 1; i < tagCounts.size(); ++i) {
        if (tagCounts[i] > tagCounts[maxIndex]) {
            maxIndex = i;
        }
    }

    return uniqueTagSizes[maxIndex];
}


	
	int findMaxTags(vector<AnimeTraits>& characters) {
    
   if (characters.empty()) return 0;
    int maxTags = characters[0].tags.size();

    for (AnimeTraits& c : characters) {
        if (c.tags.size() > maxTags) {
            maxTags = c.tags.size();
            
        }
    }

    return maxTags;
}
	
	
	Node * getTagNode(vector<AnimeTraits>characters){
		int maxTags=findCommonTagSize(characters);

		Node *node= new Node("Does your anime contain  " + to_string(maxTags) + " tags? (yes/no)",characters);
	    auto[yesGroup,noGroup]=splitByMaxTags(maxTags,characters);
	    
	    node->yes= getCharQuestion(yesGroup);
	    
	    
	       maxTags=findCommonTagSize(noGroup);
	       auto[yesGroup2,noGroup2]=splitByMaxTags(maxTags,noGroup);
	    node->no= new Node("Does your anime contain  " + to_string(maxTags) + " tags? (yes/no)", noGroup);
	    
	    

	     node->no->yes=getCharQuestion(yesGroup2);
	    
	      maxTags=findCommonTagSize(noGroup2);
	     auto[yesGroup3,noGroup3]=splitByMaxTags(maxTags,noGroup2);
	    node->no->no=new Node("Does your anime contain  " + to_string(maxTags) + " tags? (yes/no)",noGroup2);
	  
	    node->no->no->no=getCharQuestion(noGroup3);
	    node->no->no->yes=getCharQuestion(yesGroup3);
	    
	  
		return node;
	}
	
	Node *getCharQuestion(vector<AnimeTraits> &characters){
		
		return new Node("",characters);
		
		
		
		
		
	}
	
	
	
	

	
 pair<vector<AnimeTraits>,vector<AnimeTraits>>	splitByMaxTags(int maxTags,vector<AnimeTraits>&characters){
		    vector <AnimeTraits> yesGroup,noGroup;                   
	 
	         for(AnimeTraits &c:characters){
	         	if(c.tags.size()==maxTags){
	         		yesGroup.push_back(c);
				 }
				 
				 else {
				 	noGroup.push_back(c);
				 }
			 }
			 
			 return {yesGroup,noGroup};
	}
	
	
	


	void playGame()
	{
		Node *current = root;
		while (current != nullptr)
		{
			cout << current->question << endl;

	if(current->question!="")
			{
				string answer;
				cin >> answer;

				if (answer == "yes")
				{
					cout << "Characters matched: " << current->yes->characters.size() << endl;
					current = current->yes;
				}
				else if (answer == "no")
				{
					cout << "Characters matched: " << current->no->characters.size() << endl;
					current = current->no;
				}
		
				else if (answer == "other"){
				
					cout << "Characters matched: " << current->other->characters.size() << endl;
					current = current->other;
				}
					
				else
				{
					cout << "Invalid or no further node." << endl;
					break;
				}
			}
			else
			{
				// Default handling for other questions
				string answer;
				cin >> answer;

				if (answer == "yes")
					current = current->yes;
				else if (answer == "no")
					current = current->no;
				else if (answer == "other")
					current = current->other;
				else
				{
					cout << "Invalid input." << endl;
					break;
				}
			}
		}
	}
	
	
	void destroyTree(Node* node){
    if (node == nullptr)
        return;

    destroyTree(node->yes);
    destroyTree(node->no);
    destroyTree(node->other);

    delete node;
}
};
