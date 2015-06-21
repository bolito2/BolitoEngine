#pragma once

#include <vector>

class IOManager
{
public:
	static bool readFile(std::string filePath, std::vector<unsigned char>& buffer);
};

