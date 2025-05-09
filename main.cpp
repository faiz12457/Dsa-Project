#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>

using namespace std;

class AnimeTraits {
public:
    string id;
    string name;
    string hairColor;
    string gender;
    vector<string> tags;
    vector<string> anime;
    vector<string> manga;
};


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
    string FN = "data.csv";
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

int main() {
    vector<AnimeTraits> animeList;
    readData(animeList);

    if (!animeList.empty()) {
    
        for (int i = 1; i < animeList.size()&&i<1000; i++) {
            cout << "ID: " << animeList[i].id << " ";
            cout << "Name: " << animeList[i].name << " ";
            cout << "Tags: ";

            for (int j = 0; j < animeList[i].tags.size(); j++) {
                cout << animeList[i].tags[j];
                if (j != animeList[i].tags.size() - 1)
                    cout << ",";
            }
            cout << endl;
        }
    } else {
        cout << "No records found!" << endl;
    }

    return 0;
}
