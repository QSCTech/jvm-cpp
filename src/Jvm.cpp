#include "Jvm.h"
#include <iostream>
#include "ClassFile.h"

void Jvm::StartJvm(std::map<std::string, docopt::value> args)
{
	auto cp = new Classpath(args);
	auto target = args["<target>"].asString();
	std::replace(target.begin(), target.end(), '.', boost::filesystem::path::preferred_separator);
	auto cf = loadClass(target, cp);
	printClassInfo(cf);
}

ClassFile *Jvm::loadClass(std::string className, Classpath *cp)
{
	auto result = cp->ReadClass(className);
	if (result.status == STATUS_OK)
	{
		std::cout << "data(" << result.data.size() << "): " << std::endl;
		for (auto i: result.data)
		{
			printf("%X", i);
		}
		std::cout << std::endl;
		auto classFile = new ClassFile();
		auto parseResult = classFile->Parse(result.data);
		if (parseResult.status == STATUS_ERR)
		{
			std::cout << parseResult.error << std::endl;
		}
		return classFile;
	}
	std::cout << "StartJVM error: " << result.err.what() << std::endl;
	return nullptr;
}

void Jvm::printClassInfo(ClassFile *cf)
{
	if (cf != nullptr)
	{
		std::cout << "version: " << cf->MajorVersion() << "." << cf->MinorVersion() << "\n"
		          << "constants count: " << cf->GetConstantPool()->Info.size() << std::endl;
		printf("access flags: 0x%X\n", cf->AccessFlags());
		printf("this class: %s\n", cf->ClassName().c_str());
		printf("super class: %s\n", cf->SuperClassName().c_str());
		printf("interfaces: [ ");
		for(auto interface : cf->InterfaceName())
		{
			std::cout << interface <<", ";
		}
		std::cout << "]" << std::endl;
		printf("fields count: %lu\n", cf->Fields().size());
		for(auto field : cf->Fields())
		{
			printf("    %s\n", field->Name().c_str());
		}
		
		printf("methods count: %lu\n", cf->Methods().size());
		for(auto method : cf->Methods())
		{
			printf("    %s\n", method->Name().c_str());
		}
	}
}