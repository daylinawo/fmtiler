#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <vector>
#include <map>

namespace Utility
{

	int FindElemsPerRow(int ContainerWidth, int elemWidth, int gutterWidth, int totalElems);
	std::vector<std::string> ParseString(const std::string& str, char token);
	bool GetFileStrings(const std::string& path, int startPos, char endChar, std::vector<std::string>& contents);
	int FindInFile(const std::string& path, const std::string& str);
};


#endif

