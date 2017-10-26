
#ifndef JVM_CLASSPATH_H
#define JVM_CLASSPATH_H
#include <string>
#include <boost/filesystem.hpp>
#include "util.h"

class Entry;

class Classpath;

class CompositeEntry;

class WildcardEntry;

class ZipEntry;

class DirEntry;

struct ReadClassResult {std::vector<char> data; Entry & entry; FileReadError err; int status; };

class Classpath
{
  public:
	static Entry *newEntry(std::string path);
};

class Entry
{
  public:
	virtual ReadClassResult readClass(std::string className) = 0;
	virtual std::string String() = 0;
};

class DirEntry: public Entry
{
	std::string absDir;
  public:
	explicit DirEntry(std::string path) : absDir(boost::filesystem::canonical(path).string())
	{}
	
	ReadClassResult readClass(std::string className) override;
	std::string String() override;
};

class ZipEntry: public Entry
{
	std::string absPath;
  public:
	explicit ZipEntry(std::string path) : absPath(boost::filesystem::canonical(path).string())
	{}
	
	ReadClassResult readClass(std::string className) override;
	std::string String() override;
};

class CompositeEntry: public Entry
{
  public:
	explicit CompositeEntry(std::string path);
	ReadClassResult readClass(std::string className) override;
	std::string String() override;
};

class WildcardEntry: public Entry
{
  public:
	explicit WildcardEntry(std::string path);
	ReadClassResult readClass(std::string className) override;
	std::string String() override;
};

#endif
