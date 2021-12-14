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
	ifstream file("data.txt");
	mPlayerData.clear();
	data.clear();
	names.clear();
	scores.clear();
	while (getline(file, str)) 
	{
		if (str.size() > 0) {
			data.push_back(str);
		}
	}

	Decrypt();

	for (size_t i = 0; i < data.size(); ++i) 
	{
		if (i % 2 == 0) 
		{
			names.push_back(data[i]);
		}
		else 
		{
			scores.push_back(data[i]);
		}
	}

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
	ofstream file("data.txt", ios::app);
	mName = playerName;
	mScore = score;
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