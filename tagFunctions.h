#pragma once
#include <iostream>
#include "animeTraits.h"
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include "node.h"
using namespace std;


class TagQuestion{
public:
	
	// GET GENDER CHAR FUNCTION
		Node *getGenderCharTag(Node *node, string gender)
	{
		vector<AnimeTraits> genderGroup;
		for (AnimeTraits c : node->characters)
		{
			if (c.gender == gender)
			{
				genderGroup.push_back(c);
			}
		}
		
		string question="Does your anime contain natural hair? (yes/no)";
		
           return getHairColor(question,genderGroup);
	
	}
	
	

	// filter character using hair color function

pair<vector<AnimeTraits>,vector<AnimeTraits>> filterCharUsingColor(vector<AnimeTraits>&characters,string commonColor){
	   vector<AnimeTraits> yesGroup,noGroup;
        
        for(AnimeTraits &c:characters){
        	if(c.hairColor==commonColor){
        		yesGroup.push_back(c);
			}
			else{
				noGroup.push_back(c);
			}
        	
		}
		
		return {yesGroup,noGroup};
}
  
   // get split colors function based on natural and unNatural
   
   pair<vector<AnimeTraits>,vector<AnimeTraits>> splitHairColor(vector<AnimeTraits>&characters){
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
		
		return {yesGroup,noGroup};
   }
  
  
  //  GET HAIR COLOR FUNCTION 
  	Node *getHairColor(string question, vector<AnimeTraits> &characters)
	{
		
		Node *node= new Node(question,characters);
		
		auto [naturalColors,nonNaturalColors]=splitHairColor(characters);
	
		string commonColor=naturalColors[0].hairColor;
		
        commonColor=findCommonColor(naturalColors);
        
    
        
        auto[commonColorCharYes,commonColorCharNo]= filterCharUsingColor(naturalColors,commonColor);
        

		node->yes = new Node("Does your character have "+commonColor +" ? (yes/no)",naturalColors);
	    node->yes->yes=getTagSizeQuestion(commonColorCharYes);
    
		
		commonColor=findCommonColor (commonColorCharNo);
		auto[commonColorCharYes1,commonColorCharNo1]= filterCharUsingColor(commonColorCharNo,commonColor);
		
	    node->yes->no=new Node("Does your character have "+commonColor +" ? (yes/no)",commonColorCharNo1);
		node->yes->no->yes=getTagSizeQuestion(commonColorCharYes1);
		 
		 
		 
		commonColor=findCommonColor (commonColorCharNo1);
		auto[commonColorCharYes2,commonColorCharNo2]= filterCharUsingColor(commonColorCharNo1,commonColor);
			
			
		node->yes->no->no=new Node("Does your character have "+commonColor +" ? (yes/no)",commonColorCharNo1);
		node->yes->no->no->yes=getTagSizeQuestion(commonColorCharYes2);
		node->yes->no->no->no=getTagSizeQuestion(commonColorCharNo2);

	    auto[noHairColor,yesHairColor]=filterCharUsingColor(nonNaturalColors,"");	
	    node->no = new Node("Does your character have hair color (yes/no)",nonNaturalColors);
        node->no->yes=getTagSizeQuestion(yesHairColor);
    	
    	
	    node->no->no=getTagSizeQuestion(noHairColor);
   
		return node;
	}
	
	    // TAG SIZE QUESTION NODE
		Node * getTagSizeQuestion(vector<AnimeTraits>&characters){
		int maxTags=findCommonTagSize(characters);
		Node *node= new Node("Does your anime contain  " + to_string(maxTags) + " tags? (yes/no)",characters);
	    auto[yesGroup,noGroup]=splitByMaxTags(maxTags,characters);
	    
	    node->yes= getVowelQuestion(yesGroup);
	    
	    
	    maxTags=findCommonTagSize(noGroup);
	    auto[yesGroup2,noGroup2]=splitByMaxTags(maxTags,noGroup);
	    node->no= new Node("Does your anime contain  " + to_string(maxTags) + " tags? (yes/no)", noGroup);
	    
	      node->no->yes=getVowelQuestion(yesGroup2);
	    
	      maxTags=findCommonTagSize(noGroup2);
	     auto[yesGroup3,noGroup3]=splitByMaxTags(maxTags,noGroup2);
	    node->no->no=new Node("Does your anime contain  " + to_string(maxTags) + " tags? (yes/no)",noGroup2);
	  
	    node->no->no->no=getVowelQuestion(noGroup3);
	    
	    node->no->no->yes=getVowelQuestion(yesGroup3);
	    
		return node;
	}
	
	pair<vector<AnimeTraits>,vector<AnimeTraits>> splitBasedOnRange(int range,vector<AnimeTraits>&characters){
		vector<AnimeTraits> yesGroup,noGroup;
		
		for(auto c:characters){
			string allTags="";
			for(auto tag:c.tags){
				allTags+=tag;
			}
			
			int count=0;
			count=countVowels(allTags);
			
			if(count<=range){
				yesGroup.push_back(c);
			}
			else{
				noGroup.push_back(c);
			}
		}
		
		return {yesGroup,noGroup};
		
	}
	

Node* getVowelQuestion(vector<AnimeTraits>& characters, int depth=3) {
    if (depth == 0 || characters.size() <= 1) {
       return buildLengthDecisionTree(characters);        
    }

    auto [maxVowel, minVowel] = findMaxMinTagVowels(characters);
    int mid = minVowel + (maxVowel - minVowel) / 2;
    string question = "Do your character's tags contain fewer than or equal to " + to_string(mid) + " vowels? (yes/no)";
    
    Node* node = new Node(question, characters);
    
    auto [yesGroup, noGroup] = splitBasedOnRange(mid, characters);
    
    node->yes = getVowelQuestion(yesGroup, depth - 1);
    node->no = getVowelQuestion(noGroup, depth - 1);

    return node;
}





	
	
	pair<vector<AnimeTraits>,vector<AnimeTraits>> splitByCommonVowelCount(int commonCount,vector<AnimeTraits>&characters){
		
		vector <AnimeTraits>yesGroup,noGroup;
		for (auto& c : characters) {
    if (c.anime.size() > 0 and commonCount>0) {
        int count = countVowels(c.anime[0]);
        if (count == commonCount) {
            yesGroup.push_back(c);
        } else {
            noGroup.push_back(c);   
        }
    }
}
		
		return {yesGroup,noGroup};
	}
	
	
	
	
	
	
	// BUILT TAG LENGTH TREE FUNCTION
	Node* buildLengthDecisionTree(vector<AnimeTraits> characters) {
    if (characters.empty()) return nullptr;

    auto [maxLength, minLength] = findMaxMinTagLengthCharacters(characters);
       
    // Split into groups
    vector<AnimeTraits> yesGroup, noGroup;

    for (auto& c : characters) {
        if (!c.tags.empty() && c.tags[0].length() == maxLength) {
            yesGroup.push_back(c);
        } else {
            noGroup.push_back(c);
        }
    }

    // Create current node
    string question = "Does your character's first tag have length " + to_string(maxLength) + "? (yes/no)";
    Node* node = new Node(question, characters);

    
    if (yesGroup.size() == characters.size()) {
    	if(yesGroup.size()<=10){
    		node->yes =tagQuestion(yesGroup);
            node->no = nullptr;
		}
		else{
		node->yes = new Node("Group with tag length " + to_string(maxLength), yesGroup);
        node->no = nullptr;
    }
        return node;
    }
    
    
      
      if(yesGroup.size()<=10){
      	node->yes=tagQuestion(yesGroup);
      	node->no = buildLengthDecisionTree(noGroup);
	  }
	  else{
	node->yes = new Node("Group with tag length " + to_string(maxLength), yesGroup);
    node->no = buildLengthDecisionTree(noGroup);
	 }


    return node;
}



Node* tagQuestion(vector<AnimeTraits> characters) {
    if (characters.empty()) return new Node("",{});

    // Base condition: only one character left
    if (characters.size() == 1) {
        return new Node("Answer: " + characters[0].name, characters);
    }

    // Start building the decision tree
    Node* root = nullptr;
    Node* current = nullptr;

    for (int i = 0; i < characters.size(); ++i) {
        string tag = characters[i].tags[0];
        Node* questionNode = new Node("Does your character have tag \"" + tag + "\"? (yes/no)", characters);
        questionNode->yes = new Node("Answer: " + characters[i].name, {characters[i]});

        if (root == nullptr) {
            root = questionNode;
            current = questionNode;
        } else {
            current->no = questionNode;
            current = questionNode;
        }
    }

    // Final fallback node if none matched
    current->no = new Node("Character not found.", {});
    return root;
}

pair<int, int> findMaxMinTagVowels(vector<AnimeTraits>& characters) {
    if (characters.empty()) {
        return {-1, -1};
    }
    int maxVowels = -1;
    int minVowels = INT_MAX;

    for (const auto& c : characters) {
        if (!c.tags.empty()) {
    
            
            string allTags="";
            
            for(auto tag: c.tags){
            	allTags+=tag;
			}
			int count =0;
			count=countVowels(allTags);

            if (count > maxVowels) {
                maxVowels = count;
            }

            if (count <minVowels) {
                minVowels = count;
            }
        }
    }

    return {maxVowels, minVowels};
}









pair<int, int> findMaxMinTagLengthCharacters(vector<AnimeTraits>& characters) {
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

	// FIND COMMON COLOR FUNCTION
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
	   // COUNT VOWEL QUESTION
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

  // FIND COMMON VOWEL COUNT FUNCTION
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

int findCommonVowelCountAnime(vector<AnimeTraits>& characters) {
    if (characters.empty()) return 0;

    vector<int> uniqueVowelCounts;
    vector<int> vowelFrequencies;

    for (AnimeTraits& c : characters) {
    	   if (c.tags.size()>0){
		   
        int vowelCount = countVowels(c.anime[0]);
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
	// SPLIT CHARACTERS BY MAX TAGS FUNCTION
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
	
		// FIND COMMON TAG SIZE
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

	 pair<vector<AnimeTraits>,vector<AnimeTraits>>	splitByCommonAnime(int commonAnime,vector<AnimeTraits>&characters){
		    vector <AnimeTraits> yesGroup,noGroup;                   
	 
	         for(AnimeTraits &c:characters){
	         	if(c.anime.size()==commonAnime){
	         		yesGroup.push_back(c);
				 }
				 
				 else {
				 	noGroup.push_back(c);
				 }
			 }
			 
			 return {yesGroup,noGroup};
	}

// COMMON ANIME Size 
int findCommonAnimeSize(vector<AnimeTraits>& characters) {
	if (characters.empty()) return 0;
    vector<int> uniqueAnimeSizes;
    vector<int> animeCounts;

    for ( AnimeTraits& c : characters) {
        int animeSize = c.anime.size();
        bool found = false;

        for (int i = 0; i < uniqueAnimeSizes.size(); ++i) {
            if (uniqueAnimeSizes[i] == animeSize) {
                animeCounts[i]++;
                found = true;
                break;
            }
        }

        if (!found) {
            uniqueAnimeSizes.push_back(animeSize);
            animeCounts.push_back(1);
        }
    }

    int maxIndex = 0;
    for (int i = 1; i < animeCounts.size(); ++i) {
        if (animeCounts[i] > animeCounts[maxIndex]) {
            maxIndex = i;
        }
    }

    return uniqueAnimeSizes[maxIndex];
}



};
	
		
