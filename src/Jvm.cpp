#include "Jvm.h"

void Jvm::StartJvm(std::map<std::string, docopt::value> args)
{
	auto cp = new Classpath(args);
	auto target = args["<target>"].asString();
	std::replace(target.begin(), target.end(), '.', boost::filesystem::path::preferred_separator);
	auto cf = loadClass(target, cp);
	printClassInfo(cf);
	auto frame = Frame(100, 100);
	testLocalVars(frame.localVars);
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
		for (auto interface : cf->InterfaceName())
		{
			std::cout << interface << ", ";
		}
		std::cout << "]" << std::endl;
		printf("fields count: %lu\n", cf->Fields().size());
		for (auto field : cf->Fields())
		{
			printf("    %s\n", field->Name().c_str());
		}
		printf("methods count: %lu\n", cf->Methods().size());
		for (auto method : cf->Methods())
		{
			printf("    %s\n", method->Name().c_str());
		}
	}
}

void Jvm::testLocalVars(LocalVars *vars)
{
	vars->SetInt(0, 100);
	vars->SetInt(1, -100);
	vars->SetLong(2, 1312413413);
	vars->SetLong(4, -1312413413);
	vars->SetFloat(6, 3.141592);
	vars->SetDouble(7, 2.412414151351255125);
	vars->SetRef(9, nullptr);
	Test::assert_equal(100, vars->GetInt(0));
	Test::assert_equal(-100, vars->GetInt(1));
	Test::assert_equal<int64_t >(1312413413, vars->GetLong(2));
	Test::assert_equal<int64_t >(-1312413413, vars->GetLong(4));
	Test::assert_equal<float >(3.141592, vars->GetFloat(6));
	Test::assert_equal<double >(2.412414151351255125, vars->GetDouble(7));
	Test::assert_equal<Object*>(nullptr, vars->GetRef(9));
}

void Jvm::testOperandStack(OperandStack *stack)
{

}