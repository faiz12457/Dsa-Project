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
	
		root->no = new Node("is your character have all manga and anime and tags (yes/no) ", noGroup);

		root->yes->yes = getGenderChar(root->yes, "Male");
		root->yes->no = getGenderChar(root->yes, "Female");
		root->yes->other = getGenderChar(root->yes, "");

		vector<AnimeTraits> existInBothYes, existInBothNo;
		for (AnimeTraits &c : root->no->characters)
		{
			if (c.anime.size() > 0 and c.manga.size() > 0 and c.tags.size()>0)
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
	
	Node *getHairColor1(Node *root, vector<AnimeTraits> &characters)
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
		
		
		root->yes = new Node("Does your character have "+commonColor +" ? (yes/no)", yesGroup);
	    root->yes->yes=checkWhatExist(commonColorCharYes);
	
		
		
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
		 root->yes->no->yes=checkWhatExist(commonColorCharYes);
		 
		 
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
		    root->yes->no->no->yes=checkWhatExist(commonColorCharYes);
		    root->yes->no->no->no=checkWhatExist(commonColorCharNo);

			
		root->no = new Node("Does your character have hair color (yes/no)", noGroup);
    	root->no->yes=checkWhatExist(yesHairColor);
    	
    	
		root->no->no=checkWhatExist(noHairColor);
   
         
         
		return root;
	}

	
	void displayVector(const vector<string>& vec, const string& label) {
    cout << label << ": ";
    if (vec.empty()) {
        cout << "None";
    } else {
        for (const string& item : vec) {
            cout << item << ", ";
        }
    }
    cout << endl;
}

void displayAllCharacters( vector<AnimeTraits>& characters) {
    for (const auto& c : characters) {
        cout << "----------------------------------" << endl;
        cout << "ID: " << c.id << endl;
        cout << "Name: " << c.name << endl;
        cout << "Hair Color: " << c.hairColor << endl;
        cout << "Gender: " << c.gender << endl;
        displayVector(c.tags, "Tags");
        displayVector(c.anime, "Anime");
        displayVector(c.manga, "Manga");
        cout << "----------------------------------" << endl << endl;
    }
}
	
	
	Node *checkWhatExist(vector<AnimeTraits> &characters){
		cout<<characters.size()<<endl;
		displayAllCharacters(characters);
		Node *node=new Node("",characters);
		
		
		
		return node;
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

			
		root->no = new Node("Does your character have hair color (yes/no)", noGroup);
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






	
	Node * getTagNode(vector<AnimeTraits>&characters){
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
	

	
	
	int countVowels( string& str) {
		if (str.empty()) return 0;
    int count = 0;
    for (char ch : str) {
        ch = tolower(ch);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            count++;
        }
    }
    return count;
}

int findCommonVowelCount(vector<AnimeTraits>& characters) {
    if (characters.empty()) return 0;

    vector<int> uniqueVowelCounts;
    vector<int> vowelFrequencies;

    for (AnimeTraits& c : characters) {
    	   if (c.tags.size()>0){
		   
        int vowelCount = countVowels(c.tags[0]);
        bool found = false;

        for (int i = 0; i < uniqueVowelCounts.size(); i++) {
            if (uniqueVowelCounts[i] == vowelCount) {
                vowelFrequencies[i]++;
                found = true;
                break;
            }
        }

        if (!found) {
            uniqueVowelCounts.push_back(vowelCount);
            vowelFrequencies.push_back(1);
        }
    }
    }
   if (vowelFrequencies.empty()) return 0; 
    int maxIndex = 0;
    for (int i = 1; i < vowelFrequencies.size(); ++i) {
        if (vowelFrequencies[i] > vowelFrequencies[maxIndex]) {
            maxIndex = i;
        }
    }


    return uniqueVowelCounts[maxIndex];
}
	
	Node *getCharQuestion(vector<AnimeTraits> &characters){
		 	int vowelCount=0;
	vowelCount=findCommonVowelCount(characters);
	vector<AnimeTraits> yesGroup,noGroup;
	
for (auto& c : characters) {
    if (c.tags.size() > 0 and vowelCount>0) {
        int count = countVowels(c.tags[0]);
        if (count == vowelCount) {
            yesGroup.push_back(c);
        } else {
            noGroup.push_back(c);   
        }
    }
}
	
 Node *node=new Node("Does your Character first Tag contain "+ to_string(vowelCount) + " vowels? (yes/no)",characters);
 
 	     node->yes=buildLengthDecisionTree(yesGroup);
 	     node->no=buildLengthDecisionTree(noGroup);
 	
		
		return node;
	}
	
	Node* buildLengthDecisionTree(vector<AnimeTraits> characters) {
    if (characters.empty()) return nullptr;

    auto [maxLength, minLength] = findMaxMinTagLengthCharacters(characters);

    if (maxLength == -1) return nullptr; // No valid tags

    // Split into groups
    vector<AnimeTraits> yesGroup, noGroup;

    for (const auto& c : characters) {
        if (!c.tags.empty() && c.tags[0].length() == maxLength) {
            yesGroup.push_back(c);
        } else {
            noGroup.push_back(c);
        }
    }

    // Create current node
    string question = "Does your character's first tag have length " + to_string(maxLength) + "? (yes/no)";
    Node* node = new Node(question, characters);

    // Terminal condition
    if (yesGroup.size() == characters.size()) {
        node->yes = new Node("This is the character group with tag length " + to_string(maxLength), yesGroup);
        node->no = nullptr;
        return node;
    }

    node->yes = new Node("Group with tag length " + to_string(maxLength), yesGroup);
    node->no = buildLengthDecisionTree(noGroup); // Recursive call

    return node;
}

	
	
pair<int, int> findMaxMinTagLengthCharacters(const vector<AnimeTraits>& characters) {
    if (characters.empty()) {
        return {-1, -1};
    }

    int maxLength = -1;
    int minLength = INT_MAX;

    for (const auto& c : characters) {
        if (!c.tags.empty()) {
            int len = c.tags[0].length();

            if (len > maxLength) {
                maxLength = len;
            }

            if (len < minLength) {
                minLength = len;
            }
        }
    }

    return {maxLength, minLength};
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
