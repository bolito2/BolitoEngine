#pragma once

#include <vector>

namespace BolitoEngine {

	class IOManager
	{
	public:
		static bool readFile(std::string filePath, std::vector<unsigned char>& buffer);
	};

}
