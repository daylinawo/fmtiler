#include "Utility.h"
#include <fstream>
#include <string>
#include <iostream>

int Utility::FindElemsPerRow(int ContainerWidth, int elemWidth, int gutterWidth, int totalElems)
{
    int totalSize = totalElems * (elemWidth + gutterWidth);

    if (totalSize > ContainerWidth)
    {
       return FindElemsPerRow(ContainerWidth, elemWidth, gutterWidth, --totalElems);
    }
	else
	{
		return totalElems;
	}

    return 0;
}

std::vector<std::string> Utility::ParseString(const std::string& str, char token)
{
	std::string word;
	std::vector<std::string> strlist;
	for (auto it = str.begin(); it != str.end(); it++)
	{
		if ((*it) == token)
		{
			if (!word.empty())
			{
				strlist.push_back(word);
				word.clear();
			}

			continue;
		}

		word += *it;
	}

	if (!word.empty())
	{
		strlist.push_back(word);
		word.clear();
	}

	return strlist;
}

bool Utility::GetFileStrings(const std::string& path, int startPos, char endChar, std::vector<std::string>& contents)
{
	std::ifstream file(path, std::ios_base::in);

	if (file.is_open())
	{
		file.seekg(startPos);
		std::string line;

		while (std::getline(file, line))
		{
			//stop copying if the line starts 
			//with the specified character
			if (*line.begin() == endChar)
			{
				file.close();
				return true;
			}

			contents.push_back(line);
		}

		file.close();
		return true;
	}

	return false;
}


int Utility::FindInFile(const std::string& path, const std::string& str)
{
	std::ifstream file;
	
	file.open(path, std::ios_base::in);

	if (file.is_open())
	{
		std::string line;

		while (std::getline(file, line))
		{
			if (line == str)
			{
				return static_cast<int>(file.tellg());
			}
		}

		file.close();
	}

	return NULL;
}
