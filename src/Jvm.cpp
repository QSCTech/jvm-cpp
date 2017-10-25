//
// Created by 李晨曦 on 25/10/2017.
//

#include "Jvm.h"
#include <iostream>

void Jvm::StartJvm(std::map<std::string, docopt::value> args)
{
	std::cout << "Starting JVM: " << args["<file>"] << std::endl;
}
