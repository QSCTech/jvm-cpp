#ifndef JVM_JVM_H
#define JVM_JVM_H

#include "docopt.h"
#include "util.h"
#include "ClassFile.h"

class Jvm
{
  public:
	static void StartJvm(std::map<std::string, docopt::value>);
};

#endif
