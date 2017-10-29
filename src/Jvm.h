#ifndef JVM_JVM_H
#define JVM_JVM_H

#include "docopt.h"
#include "util.h"
#include "ClassFile.h"
#include "classpath.h"

class Jvm
{
  public:
	static void StartJvm(std::map<std::string, docopt::value>);
	static ClassFile* loadClass(std::string className, Classpath* cp);
	static void printClassInfo(ClassFile* cf);
};

#endif
