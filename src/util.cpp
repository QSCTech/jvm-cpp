#include <vector>
#include "util.h"

ReadResult util::ReadAllBytes(std::string filename)
{
	std::ifstream ifs(filename, std::ios::binary | std::ios::in);
	std::vector<BYTE> result;
	if(ifs.fail())
	{
		return {result, FileReadError(filename), STATUS_ERR};
	}
	std::copy(std::istream_iterator<BYTE>(ifs), std::istream_iterator<BYTE>(), std::back_inserter(result));
	return {result, FileReadError(""), STATUS_OK};
}