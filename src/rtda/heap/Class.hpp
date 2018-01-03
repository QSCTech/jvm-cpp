//
// Created by 李晨曦 on 11/12/2017.
//

#ifndef JVM_CLASS_HPP
#define JVM_CLASS_HPP
#include <cstdint>
#include <string>
#include <vector>
#include "ConstantPool.hpp"
#include "Slot.hpp"
#include "ClassFile.hpp"
#include "AccessFlags.hpp"

class Class;

class ClassMember;

class Field;

class Method;

class ClassLoader;

class Class
{
	uint16_t accessFlag;
	std::string name;
	std::string superClassName;
	std::vector<std::string> interfaceNames;
	ConstantPool *constantPool;
	std::vector<Field *> fields;
	std::vector<Method *> methods;
	ClassLoader *loader;
	Class *superClass;
	std::vector<Class *> interfaces;
	uint32_t instanceSlotCount;
	uint32_t staticSlotCount;
	Slot *staticVars;
	template <class T>
	std::vector<T *> load(std::vector<MemberInfo *>);
  public:
	explicit Class(ClassFile *cf);
	bool IsPublic();
	bool IsFinal();
	bool IsSuper();
	bool IsInterface();
	bool IsAbstract();
	bool IsSynthetic();
	bool IsAnnotition();
	bool IsEnum();
};

class ClassMember
{
	uint16_t accessFlags;
	std::string name;
	std::string descriptor;
	Class *belongClass;
  public:
	ClassMember(MemberInfo *memberInfo, Class *belongClass);
};

class Field: public ClassMember
{
  public:
	Field(MemberInfo *memberInfo, Class *belongClass);
};

class Method: public ClassMember
{
	uint32_t maxStack;
	uint32_t maxLocals;
	std::vector<byte> code;
  public:
	Method(MemberInfo *memberInfo,
	Class *belongClass);
};


inline bool Class::IsPublic()
{
	return 0 != (accessFlag & AccessFlags::ACC_PUBLIC);
}

inline bool Class::IsFinal()
{
	return 0 != (accessFlag & AccessFlags::ACC_FINAL);
}

inline bool Class::IsSuper()
{
	return 0 != (accessFlag & AccessFlags::ACC_SUPER);
}

inline bool Class::IsInterface()
{
	return 0 != (accessFlag & AccessFlags::ACC_INTERFACE);
}

inline bool Class::IsAbstract()
{
	return 0 != (accessFlag & AccessFlags::ACC_ABSTRACT);
}

inline bool Class::IsSynthetic()
{
	return 0 != (accessFlag & AccessFlags::ACC_SYNTHETIC);
}

inline bool Class::IsAnnotition()
{
	return 0 != (accessFlag & AccessFlags::ACC_ANNOTATION);
}

inline bool Class::IsEnum()
{
	return 0 != (accessFlag & AccessFlags::ACC_ENUM);
}

template<class T>
std::vector<T *> Class::load(std::vector<MemberInfo *> membersInfos)
{
	auto results = std::vector<T *>();
	for (auto memberInfo : membersInfos)
	{
		results.push_back(new T(memberInfo, this));
	}
	return results;
}

#endif //JVM_CLASS_HPP
