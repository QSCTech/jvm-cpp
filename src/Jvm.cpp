#include "Jvm.h"
#include "classpath.h"
#include <iostream>

void Jvm::StartJvm(std::map<std::string, docopt::value> args)
{
	std::cout << "Starting JVM: " << args["<target>"] << std::endl;
	std::cout << "Xjre: " << args["--Xjre"] << std::endl;
	auto cp = new Classpath(args);
	std::cout << cp->String() << std::endl;
	
	auto target = args["<target>"].asString();
	std::replace(target.begin(), target.end(), '.', boost::filesystem::path::preferred_separator);
	auto result = cp->ReadClass(target);
	if(result.status == STATUS_OK)
	{
		std::cout << "data: " << std::endl;
		for(auto i: result.data)
		{
			std::cout << i << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << "Error: " << result.err.what() << std::endl;
}
