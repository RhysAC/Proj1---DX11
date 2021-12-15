#include "DataBase.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void DataBase::RecoverData() 
{
	string str;
	//Find file data.txt
	ifstream file("data.txt");
	//clear all vectors in case the programm has not stopped running, so we don't get duplicate data
	mPlayerData.clear();
	data.clear();
	names.clear();
	scores.clear();
	//Put each line into the data vector
	while (getline(file, str)) 
	{
		if (str.size() > 0) {
			data.push_back(str);
		}
	}

	//Decrypt the data 
	Decrypt();

	//Becuase of how we laid out the text file, an even entry in the vector will be a name
	for (size_t i = 0; i < data.size(); ++i) 
	{
		//if even
		if (i % 2 == 0) 
		{
			//add to the names vector
			names.push_back(data[i]);
		}
		//if odd
		else 
		{
			//add to the scores vector
			scores.push_back(data[i]);
		}
	}

	//now add each name and corresponding score to the player data vector, pairing both together
	for (size_t i = 0; i < names.size(); ++i) 
	{
		mPlayerData.push_back(PlayerData{ names[i], scores[i] });
	}

	file.close();
}

void DataBase::Decrypt()
{
	const int key = 20;
	int stringLength = 0;
	char* cString = nullptr;

	for (size_t i = 0; i < data.size(); ++i)
	{
		stringLength = data[i].length();
		cString = (char*)(data[i].c_str());
		for (size_t i = 0; i < stringLength; ++i)
		{
			*(cString + i) = (*(cString + i) ^ key);
		}
	}
}

void DataBase::SaveData(const std::string playerName, float score)
{
	//Ios::app adds to the file instead of overwriting it
	ofstream file("data.txt", ios::app);
	//Get the current name and score
	mName = playerName;
	mScore = score;
	//Encrypt the data and then write it to the file
	Encrypt();
	file << mName << '\n';
	file << mScoreString << '\n';
	file.close();
}

void DataBase::Encrypt()
{
	const int key = 20;
	int stringLength = mName.length();
	char* cString = (char*)(mName.c_str());
	for (size_t i = 0; i < stringLength; ++i)
	{
		*(cString + i) = (*(cString + i) ^ key);
	}

	//convert score to a string first
	mScoreString = to_string(mScore).substr(0, 3);
	stringLength = mScoreString.length();
	cString = (char*)(mScoreString.c_str());
	for (size_t i = 0; i < stringLength; ++i)
	{
		*(cString + i) = (*(cString + i) ^ key);
	}
}

void DataBase::SortAndUpdatePlayerData()
{
	// This struct checks through the data to see if score 'a' is greater than 'b', it is returned as a bool and passed in to be sorted
	struct {
		bool operator()(const PlayerData& a, const PlayerData& b) const
		{
			return stof(a.score) > stof(b.score);
		}
	} customLess;

	sort(mPlayerData.begin(), mPlayerData.end(), customLess);
}