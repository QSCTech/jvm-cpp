//
// Created by 李晨曦 on 11/12/2017.
//

#ifndef JVM_CLASS_HPP
#define JVM_CLASS_HPP
#include <cstdint>
#include <string>
#include <vector>
#include "classpath.hpp"
#include "ClassFile.hpp"
#include "AccessFlags.hpp"

class Class;

class ClassMember;

class Field;

class Method;

class ClassLoader;

extern std::string ObjectClass;

class Object;

union DoubleUnion;

union Slot;

class Slots;

class Class
{
  public:
	uint16_t getAccessFlag() const;
	const std::string &getSuperClassName() const;
	const std::vector<std::string> &getInterfaceNames() const;
	ConstantPool *getConstantPool() const;
	const std::vector<Field *> &getFields() const;
	const std::vector<Method *> &getMethods() const;
	ClassLoader *getLoader() const;
	Class *getSuperClass() const;
	const std::vector<Class *> &getInterfaces() const;
	uint32_t getInstanceSlotCount() const;
	void setSuperClass(Class *superClass);
	uint32_t getStaticSlotCount() const;
	Slots *getStaticVars() const;
  private:
	uint16_t accessFlag;
	std::string name;
	std::string superClassName;
	std::vector<std::string> interfaceNames;
	ConstantPool *constantPool;
	std::vector<Field *> fields;
	std::vector<Method *> methods;
	ClassLoader *loader;
  public:
	void setLoader(ClassLoader *loader);
  private:
	Class *superClass;
	std::vector<Class *> interfaces;
  public:
	void setInterfaces(const std::vector<Class *> &interfaces);
  private:
	uint32_t instanceSlotCount;
	uint32_t staticSlotCount;
	Slots *staticVars;
	template<class T>
	std::vector<T *> load(std::vector<MemberInfo *>);
  public:
	explicit Class(ClassFile *cf);
	const std::string &getName() const;
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
	uint32_t slotId;
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


class ClassLoader
{
	Classpath *cp;
	std::map<std::string, Class *> classMap;
	ReadClassResult ReadClass(std::string className);
	Class *loadNoArrayClass(std::string className);
	Class *defineClass(std::vector<byte> data);
	Class *parseClass(std::vector<byte> data);
	void resolveSuperClass(Class *itemClass);
	void resolveInterfaces(Class *itemClass);
  public:
	explicit ClassLoader(Classpath *cp);
	Class *LoadClass(std::string className);
	static void link(Class *newClass);
	static void verify(Class *newClass);
	static void prepare(Class *newClass);
	static void calcInstanceFieldSlotsId(Class *newClass);
	static void calcStaticFieldSlotsId(Class *newClass);
	static void allocAndInitStaticVars(Class *newClass);
};

class Object
{
	Class *ownClass;
	Slots fields;
};

union DoubleUnion
{
	double value;
	int32_t storage[2];
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

inline const std::string &Class::getName() const
{
	return name;
}

inline void Class::setSuperClass(Class *superClass)
{
	Class::superClass = superClass;
}

inline uint16_t Class::getAccessFlag() const
{
	return accessFlag;
}

inline const std::string &Class::getSuperClassName() const
{
	return superClassName;
}

inline const std::vector<std::string> &Class::getInterfaceNames() const
{
	return interfaceNames;
}

inline ConstantPool *Class::getConstantPool() const
{
	return constantPool;
}

inline const std::vector<Field *> &Class::getFields() const
{
	return fields;
}

inline const std::vector<Method *> &Class::getMethods() const
{
	return methods;
}

inline ClassLoader *Class::getLoader() const
{
	return loader;
}

inline Class *Class::getSuperClass() const
{
	return superClass;
}

inline const std::vector<Class *> &Class::getInterfaces() const
{
	return interfaces;
}

inline uint32_t Class::getInstanceSlotCount() const
{
	return instanceSlotCount;
}

inline uint32_t Class::getStaticSlotCount() const
{
	return staticSlotCount;
}

inline Slots *Class::getStaticVars() const
{
	return staticVars;
}

inline void Class::setInterfaces(const std::vector<Class *> &interfaces)
{
	Class::interfaces = interfaces;
}

inline void Class::setLoader(ClassLoader *loader)
{
	Class::loader = loader;
}

#endif //JVM_CLASS_HPP
