#ifndef JVM_JVM_H
#define JVM_JVM_H
#include "docopt.h"
#include "util.h"
#include "ClassFile.h"
#include "classpath.h"
#include "Frame.h"
#include "Slot.h"
#include <iostream>

class Jvm;

namespace Test
{
	template<class T>
	void assert_equal(T left, T right);
}

class Jvm
{
  public:
	static void StartJvm(std::map<std::string, docopt::value>);
	static ClassFile *loadClass(std::string className, Classpath *cp);
	static void printClassInfo(ClassFile *cf);
	static void testLocalVars(LocalVars *vars);
	static void testOperandStack(OperandStack *stack);
};

template<class T>
void Test::assert_equal(T left, T right)
{
	if (left != right)
	{
		std::cerr << left << " != " << right << " !\n" << std::endl;
	}
}


#endif
