#pragma once
#include <vector>
#include <fstream>
class DataBase
{
public:
	std::vector<std::string> data;
	std::vector<std::string> names;
	std::vector<std::string> scores;

	struct PlayerData {
		std::string name;
		std::string score;
	};

	void RecoverData();
	void Decrypt();
	void SaveData(const std::string playerName, float score);
	void Encrypt();
	/*A function that sorts the player data dependant upon the values of the given variables
	*IN :
	*OUT :
	*PRE_CONDITION : A valid set of data must have been established, for example a score or name must be present
	*POST_CONDITION : The data will be sorted by who has the highest score to be used later when rendering the information */
	void SortAndUpdatePlayerData();

	std::vector<PlayerData> mPlayerData;

private:
	std::string mName;
	std::string mScoreString;
	float mScore;
};

