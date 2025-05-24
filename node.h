#pragma once
#include "iostream"
#include "animeTraits.h"
using namespace std;

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
