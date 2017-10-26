#include "Jvm.h"
#include "classpath.h"
#include <iostream>

void Jvm::StartJvm(std::map<std::string, docopt::value> args)
{
	std::cout << "Starting JVM: " << args["<file>"] << std::endl;
}
