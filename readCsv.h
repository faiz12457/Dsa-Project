#pragma once
#include<iostream>
#include "animeTraits.h"
#include "sstream"
#include "fstream"
using namespace std;



class ReadCSV{
	public:
		
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}

vector<string> splitCSVLine(const string& line) {
    vector<string> fields;
    bool insideQuotes = false;
    string field;

    for (char c : line) {
        if (c == '"') {
            insideQuotes = !insideQuotes;
        } else if (c == ',' && !insideQuotes) {
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
        }
    }

    fields.push_back(field); 
    return fields;
}

// Parse a string like "['Tag1', 'Tag2']" into a vector of strings
vector<string> parseData(string line) {
    vector<string> result;

    // Remove surrounding brackets if present
    if (!line.empty() && line.front() == '[') line = line.substr(1);
    if (!line.empty() && line.back() == ']') line.pop_back();

    string val;
    stringstream ss(line);

    while (getline(ss, val, ',')) {
        val = trim(val);
        if (!val.empty() && val.front() == '\'') val = val.substr(1);
        if (!val.empty() && val.back() == '\'') val.pop_back();
        result.push_back(val);
    }

    return result;
}

void readData(vector<AnimeTraits>& animeList) {
   // string FN = "data.csv";
   // string FN="smallfile.csv";
   string FN ="anime.csv";
    ifstream checkData(FN);

    if (!checkData.is_open()) {
        cout << "Error opening file\n";
        return;
    }

    string line;
    while (getline(checkData, line)) {
        vector<string> fields = splitCSVLine(line);
       
        AnimeTraits at;
        at.id =fields[0];
        at.name = fields[1];
        at.hairColor = fields[2];
        at.gender = fields[3];

        at.tags = parseData(fields[4]);
        at.anime = parseData(fields[5]);
        at.manga = parseData(fields[6]);

        animeList.push_back(at);
    }

    checkData.close();
}

};