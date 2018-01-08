//
// Created by 李晨曦 on 11/12/2017.
//

#include "Class.hpp"

std::string ObjectClass = "java/lang/Object";

Class::Class(ClassFile *cf)
: accessFlag(cf->AccessFlags()), name(cf->ClassName()), superClassName(cf->SuperClassName()),
  interfaceNames(cf->InterfaceName()), superClass(nullptr),
  constantPool(cf->GetConstantPool()), fields(load<Field>(cf->Fields())), methods(load<Method>(cf->Methods()))
{}

ClassMember::ClassMember(MemberInfo *memberInfo, Class *belongClass)
: accessFlags(memberInfo->AccessFlags()), name(memberInfo->Name()), descriptor(memberInfo->Descriptor()),
  belongClass(belongClass)
{}

Field::Field(MemberInfo *memberInfo, Class *belongClass) : ClassMember(memberInfo, belongClass)
{}


Method::Method(MemberInfo *memberInfo,
Class *belongClass
) : ClassMember(memberInfo, belongClass), maxStack(memberInfo->getCodeAttribute()->getMaxStack()),
    maxLocals(memberInfo->getCodeAttribute()->getMaxLocals()),
    code(memberInfo->getCodeAttribute()->getCode())
{}


ClassLoader::ClassLoader(Classpath *cp) : cp(cp), classMap(std::map<std::string, Class *>())
{}

ReadClassResult ClassLoader::ReadClass(std::string className)
{
	auto result = cp->ReadClass(className);
	if (result.status == STATUS_ERR)
	{
		throw JavaClassNotFoundException(className);
	}
	return result;
}

Class *ClassLoader::loadNoArrayClass(std::string className)
{
	auto result = ReadClass(className);
	auto newClass = defineClass(result.data);
	link(newClass);
	std::cout << "Loaded " << className << " from " << result.entry;
	return newClass;
}

Class *ClassLoader::LoadClass(std::string className)
{
	if (classMap.find(className) != classMap.end())
	{
		return classMap[className];
	}
	return loadNoArrayClass(className);
}

Class *ClassLoader::defineClass(std::vector<byte> data)
{
	auto newClass = parseClass(move(data));
	newClass->setLoader(this);
	resolveSuperClass(newClass);
	resolveInterfaces(newClass);
	classMap[newClass->getName()] = newClass;
	return newClass;
}

Class *ClassLoader::parseClass(std::vector<byte> data)
{
	auto newClass = new ClassFile();
	auto Result = newClass->Parse(std::move(data));
	if (Result.status == STATUS_ERR)
	{
		throw JavaClassFormatError(Result.error);
	}
	return new Class(newClass);
}

void ClassLoader::resolveSuperClass(Class *itemClass)
{
	if (itemClass->getName() != ObjectClass)
	{
		itemClass->setSuperClass(itemClass->getLoader()->LoadClass(itemClass->getSuperClassName()));
	}
}

void ClassLoader::resolveInterfaces(Class *itemClass)
{
	auto interfacesCount = itemClass->getInterfaceNames().size();
	if (interfacesCount > 0)
	{
		auto interfaces = std::vector<Class *>(0);
		for (auto &name : itemClass->getInterfaceNames())
		{
			interfaces.push_back(itemClass->getLoader()->LoadClass(name));
		}
	}
	
}

void ClassLoader::link(Class *newClass)
{
	verify(newClass);
	prepare(newClass);
}

void ClassLoader::verify(Class *newClass)
{

}

void ClassLoader::prepare(Class *newClass)
{
	calcInstanceFieldSlotsId(newClass);
	calcStaticFieldSlotsId(newClass);
	allocAndInitStaticVars(newClass);
}

void ClassLoader::calcInstanceFieldSlotsId(Class *newClass)
{
	uint32_t slotId = 0;
	if (newClass->getSuperClass() != nullptr)
	{
		auto slotID = newClass->getSuperClass()->getInstanceSlotCount();
	}
	for (auto field: newClass->getFields()) {
		if !field.
	}
}

void ClassLoader::calcStaticFieldSlotsId(Class *newClass)
{

}

void ClassLoader::allocAndInitStaticVars(Class *newClass)
{

}
