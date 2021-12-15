#pragma once
#include <vector>
#include <fstream>
class DataBase
{
public:
	//vector for all data
	std::vector<std::string> data;
	//vector for just names
	std::vector<std::string> names;
	//vector for just scores
	std::vector<std::string> scores;

	struct PlayerData {
		std::string name;
		std::string score;
	};
	/*A function that reads the data from the text file and sorts it into the corresponding vectors
	*IN :
	*OUT :
	*PRE_CONDITION : A valid file must be used
	*POST_CONDITION : The data will be brought into the data vector to then be sorted */
	void RecoverData();
	/*A function that decrypts the encrypted data by Xor'ing the value with a given key
	*IN :
	*OUT :
	*PRE_CONDITION : A valid set of data must have been established, and the key must be the same one used when encrypting
	*POST_CONDITION : The data will be changed back to it's original format*/
	void Decrypt();
	/*A function that writes data to a text file, The data is written line by line starting with the name then score
	*IN :const string playerName, float score
	*OUT :
	*PRE_CONDITION : A valid file must be used, if the file does not exist it will be created
	*POST_CONDITION : Data will be written to a text file in the mentioned format */
	void SaveData(const std::string playerName, float score);
	/*A function that Encrypts data by Xor'ing the value with a given key
	*IN :
	*OUT :
	*PRE_CONDITION : A valid set of data must have been established, and a key must be set
	*POST_CONDITION : The data will be changed to a different character*/
	void Encrypt();
	/*A function that sorts the player data dependant upon the values of the given variables
	*IN :
	*OUT :
	*PRE_CONDITION : A valid set of data must have been established, for example a score or name must be present
	*POST_CONDITION : The data will be sorted by who has the highest score to be used later when rendering the information */
	void SortAndUpdatePlayerData();

	//vector of player data where each entry has a name and a corresponding score
	std::vector<PlayerData> mPlayerData;

private:
	//Temp variables to be used when manipulating the given values
	std::string mName;
	std::string mScoreString;
	float mScore;
};

