#include <iostream>
#include "docopt.h"
#include "Jvm.h"

static const char USAGE[] =
R"(Jvm.

    Usage:
	jvm <file>
	jvm (-j | --jar) <file>
	jvm (-h | --help)
	jvm (-v | --version)

    Options:
	-j --jar          run jar file
	-h --help         Show this screen.
	-v --version      Show version.
)";


int main(int argc, char **argv)
{
	std::map<std::string, docopt::value> args
	= docopt::docopt(USAGE,
	                 {argv + 1, argv + argc},
	                 true,
	                 "Jvm 2.0");
	Jvm::StartJvm(args);
}
