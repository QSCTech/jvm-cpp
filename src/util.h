#ifndef JVM_UTIL_H
#define JVM_UTIL_H
#define STATUS_ERR 1
#define STATUS_OK 0
#define byte uint8_t
#include <fstream>
#include <vector>
#include <string>
#include "error.h"
struct ReadResult
{
	std::vector<byte> data;
	FileReadError err;
	int status;
};

namespace util
{
	ReadResult ReadAllBytes(std::string filename);
}
#endif
