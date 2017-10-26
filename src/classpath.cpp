#include "classpath.h"
#include <zip.h>
#include <boost/algorithm/string.hpp>
#include <dirent.h>
#include <boost/algorithm/string/predicate.hpp>

using namespace boost::algorithm;
using namespace boost::filesystem;

Entry *Classpath::newEntry(const std::string path)
{
	if (path.find(';') != std::string::npos || path.find(':') != std::string::npos)
	{
		return new CompositeEntry(path);
	}
	if (ends_with(path, "*"))
	{
		return new WildcardEntry(path);
	}
	if (ends_with(path, ".jar") || ends_with(path, "JAR") || ends_with(path, "zip") || ends_with(path, "ZIP"))
	{
		return new ZipEntry(path);
	}
	return new DirEntry(path);
}

ReadClassResult DirEntry::readClass(std::string className)
{
	path pathStr(absDir);
	pathStr /= className;
	ReadResult result = util::ReadAllBytes(pathStr.string());
	return {result.data, *this, result.err, result.status};
}

std::string DirEntry::String()
{
	return this->absDir;
}

ReadClassResult ZipEntry::readClass(std::string className)
{
	int err = 0, stat;
	struct zip_stat status;
	char *contents;
	zip_file *file;
	zip *zip_f = zip_open(this->absPath.c_str(), 0, &err);
	std::vector<char> data;
	if (zip_f == NULL)
	{
		return {data, *this, FileReadError(this->absPath), STATUS_ERR};
	}
	zip_stat_init(&status);
	stat = zip_stat(zip_f, className.c_str(), 0, &status);
	if (stat == -1)
	{
		return {data, *this, FileReadError(className), STATUS_ERR};
	}
	contents = new char[status.size];
	file = zip_fopen(zip_f, className.c_str(), 0);
	zip_fread(file, contents, status.size);
	zip_fclose(file);
	zip_close(zip_f);
	data = std::vector<char>(contents, contents + status.size);
	return {data, *this, FileReadError(""), STATUS_OK};
}

std::string ZipEntry::String()
{
	return this->absPath;
}

CompositeEntry::CompositeEntry(const std::string pathList) : pathList(pathList)
{
	std::vector<std::string> paths;
	if (pathList.find(':'))
	{
		split(paths, pathList, is_any_of(":"));
	} else if (pathList.find(';'))
	{
		split(paths, pathList, is_any_of(";"));
	}
	for (auto path: paths)
	{
		this->Entries.push_back(Classpath::newEntry(path));
	}
}

CompositeEntry::~CompositeEntry()
{
	for (auto entry : this->Entries)
	{
		delete entry;
	}
}

ReadClassResult CompositeEntry::readClass(std::string className)
{
	for (auto entry : this->Entries)
	{
		ReadClassResult result = entry->readClass(className);
		if (result.status == STATUS_OK)
		{
			return result;
		}
	}
	return {std::vector<char>(), *this, FileReadError(""), STATUS_ERR};
}

std::string CompositeEntry::String()
{
	return this->pathList;
}

WildcardEntry::~WildcardEntry()
{
	for (auto entry : this->Entries)
	{
		delete entry;
	}
}

WildcardEntry::WildcardEntry(const std::string path): baseDir(boost::filesystem::canonical(path).string())
{
	struct dirent * file;
	baseDir.pop_back();
	auto dir = opendir(baseDir.c_str());
	if(dir == NULL)
	{
		throw DirOpenError(baseDir);
	}
	while ((file = readdir(dir)) != NULL) {
		if(file->d_type == DT_DIR) continue;
		std::string filename(file->d_name);
		if(ends_with(filename, ".jar") || ends_with(filename, "JAR"))
		{
			Entries.push_back(new ZipEntry(filename));
		}
	}
	if(this->Entries.size() == 0)
	{
		throw FileNotFoundError(baseDir);
	}
}

ReadClassResult WildcardEntry::readClass(std::string className)
{
	for (auto entry : this->Entries)
	{
		ReadClassResult result = entry->readClass(className);
		if (result.status == STATUS_OK)
		{
			return result;
		}
	}
	return {std::vector<char>(), *this, FileReadError(""), STATUS_ERR};
}

std::string WildcardEntry::String()
{
	return this->baseDir;
}