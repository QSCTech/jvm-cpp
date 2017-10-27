#ifndef JVM_UTIL_H
#define JVM_UTIL_H
#define STATUS_ERR 1
#define STATUS_OK 0
#define BYTE unsigned char
#include <fstream>
#include <vector>
#include <string>

class FileReadError;

class DirOpenError;

struct ReadResult;

class FileReadError: std::exception
{
	std::string errString;
  public:
	explicit FileReadError(std::string filename)
	{
		errString = "Read file error: " + filename;
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class DirOpenError: std::exception
{
	std::string errString;
  public:
	explicit DirOpenError(std::string filename)
	{
		errString = "Open dir error: " + filename;
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class FileNotFoundError: std::exception
{
	std::string errString;
  public:
	explicit FileNotFoundError(std::string filename)
	{
		errString = "Jar file not found: " + filename;
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class JavaSrcError: std::exception
{
	std::string errString;
  public:
	explicit JavaSrcError(std::string filename)
	{
		errString = filename + " , ./jre or JAVA_HOME not exist or open fail";
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};


struct ReadResult
{
	std::vector<BYTE> data;
	FileReadError err;
	int status;
};

namespace util
{
	ReadResult ReadAllBytes(std::string filename);
}
#endif
