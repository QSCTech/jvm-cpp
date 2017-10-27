#include "Jvm.h"
#include "classpath.h"
#include <iostream>

void Jvm::StartJvm(std::map<std::string, docopt::value> args)
{
	std::cout << "Starting JVM: " << args["<target>"] << std::endl;
	std::cout << "Xjre: " << args["--Xjre"] << std::endl;
}
