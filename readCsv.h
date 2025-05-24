#pragma once
#include <iostream>
#include "animeTraits.h"
#include "sstream"
#include "fstream"
using namespace std;

class ReadCSV
{
public:
    vector<string> splitLine(string line)
    {
        stringstream ss(line);
        vector<string> arr;
        string tag;
        while (getline(ss, tag, '.'))
        {
            arr.push_back(tag);
        }
        return arr;
    }

    void readData(vector<AnimeTraits> &animeList)
    {

        string FN = "anime1.csv";
        ifstream checkData(FN);

        if (!checkData.is_open())
        {
            cout << "Error opening file\n";
            return;
        }

        string line, id, name, hairColor, gender, tags, anime, manga;
        while (getline(checkData, line))
        {

            stringstream ss(line);

            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, hairColor, ',');
            getline(ss, gender, ',');
            getline(ss, tags, ',');
            getline(ss, anime, ',');
            getline(ss, manga, ',');

            AnimeTraits at;
            at.id = id;
            at.name = name;
            at.hairColor = hairColor;
            at.gender = gender;

            at.tags = splitLine(tags);
            at.anime = splitLine(anime);
            at.manga = splitLine(manga);

            animeList.push_back(at);
        }

        checkData.close();
    }
};