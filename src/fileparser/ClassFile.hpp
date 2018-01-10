#ifndef JVM_CLASSFILE_H
#define JVM_CLASSFILE_H
#include "util.hpp"
#include "ConstantPool.hpp"
#include "AttributeInfo.hpp"
#include <map>

/*
ClassFile {
    u4             magic;
    u2             minor_version;
    u2             major_version;
    u2             constant_pool_count;
    cp_info        constant_pool[constant_pool_count-1];
    u2             access_flags;
    u2             this_class;
    u2             super_class;
    u2             interfaces_count;
    u2             interfaces[interfaces_count];
    u2             fields_count;
    field_info     fields[fields_count];
    u2             methods_count;
    method_info    methods[methods_count];
    u2             attributes_count;
    attribute_info attributes[attributes_count];
}
*/
class ClassFile;

struct ParseResult;

class MemberInfo;

class ClassFile
{
	uint32_t magic;
	uint16_t minorVersion;
	uint16_t majorVersion;
	ConstantPool *cp;
	uint16_t accessFlags;
	uint16_t thisClass;
	uint16_t superClass;
	std::vector<uint16_t> interfaces;
	std::vector<MemberInfo *> fields;
	std::vector<MemberInfo *> methods;
	std::vector<AttributeInfo *> attributes;
	ParseResult Read(ClassReader *reader);
	ParseResult readAndCheckMagic(ClassReader *reader);
	ParseResult readAndCheckVersion(ClassReader *reader);
  public:
	uint16_t MinorVersion();
	uint16_t MajorVersion();
	ConstantPool *GetConstantPool();
	uint16_t AccessFlags();
	std::vector<MemberInfo *> Fields();
	std::vector<MemberInfo *> Methods();
	std::string ClassName();
	std::string SuperClassName();
	std::vector<std::string> InterfaceName();
	
	explicit ClassFile()
	: magic(0), minorVersion(0), majorVersion(0), cp(nullptr), accessFlags(0), thisClass(0), superClass(0)
	{};
	ParseResult Parse(std::vector<byte> classData);
	MemberInfo* getMainMethod();
};

struct ParseResult
{
	std::string error;
	int status;
};

class MemberInfo
{
	ConstantPool *constantPool;
	uint16_t accessFlags;
	uint16_t nameIndex;
	uint16_t descriptorIndex;
	std::vector<AttributeInfo *> attributes;
  public:
	MemberInfo(ConstantPool *cp,
	uint16_t accessFlags,
	uint16_t nameIndex,
	uint16_t descriptorIndex,
	std::vector<AttributeInfo *> attributes)
	: constantPool(cp), accessFlags(accessFlags), nameIndex(nameIndex), descriptorIndex(descriptorIndex),
	  attributes(attributes)
	{}
	
	static std::vector<MemberInfo *> readMembers(ClassReader *reader, ConstantPool *constantPool);
	static MemberInfo *readMember(ClassReader *reader, ConstantPool *constantPool);
	uint16_t AccessFlags();
	std::string Name();
	std::string Descriptor();
	CodeAttribute* getCodeAttribute();
	ConstantValueAttribute* getConstantValueAttribute();
};

#endif
