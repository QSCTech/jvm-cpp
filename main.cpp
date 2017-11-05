#include <iostream>
#include "Jvm.hpp"

static const char USAGE[] =
R"(Jvm.

    Usage:
	jvm <target> [options]
	jvm (-j | --jar) <target> [options]
	jvm (-h | --help)
	jvm (-v | --version)

    Options:
	-j --jar                run jar file
	-h --help               Show this screen.
	-v --version            Show version.
	-x --Xjre PATH          Jvm boot path
			[default: $JAVA_HOME]
	-c --classpath CP       boot path of users
			[default: ./]
)";


int main(int argc, char **argv)
{
	std::map<std::string, docopt::value> args
	= docopt::docopt(USAGE,
	                 {argv + 1, argv + argc},
	                 true,
	                 "Jvm 2.0");
	for(auto arg : args)
	{
		std::cout << arg.first << ": " << arg.second << std::endl;
	}
	Jvm::StartJvm(args);
}
