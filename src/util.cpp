#include <vector>
#include "util.hpp"

ReadResult util::ReadAllBytes(std::string filename)
{
	FILE *filePtr;
	byte *buffer;
	uint64_t fileLen;
	std::vector<byte> result;
	filePtr = std::fopen(filename.c_str(), "rb");
	std::fseek(filePtr, 0, SEEK_END);
	fileLen = static_cast<uint64_t>(std::ftell(filePtr));
	std::rewind(filePtr);
	buffer = new byte[fileLen];
	result = std::vector<byte>(fileLen);
	std::fread(buffer, fileLen, 1, filePtr);
	std::fclose(filePtr);
	for(int i = 0; i < fileLen; i++)
	{
		result[i] = buffer[i];
	}
	delete buffer;
	return {result, FileReadError(""), STATUS_OK};
}