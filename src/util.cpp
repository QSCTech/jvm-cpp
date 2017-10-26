#include <vector>
#include "util.h"

ReadResult util::ReadAllBytes(std::string filename)
{
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	std::vector<char> result;
	if(!ifs)
	{
		return {result, FileReadError(filename), STATUS_ERR};
	}
	std::ifstream::pos_type pos = ifs.tellg();
	result.reserve(pos);
	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);
	ifs.close();
	return {result, FileReadError(""), STATUS_OK};
}