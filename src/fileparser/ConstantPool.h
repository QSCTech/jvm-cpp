//
// Created by 李晨曦 on 29/10/2017.
//

#ifndef JVM_CONSTANTPOOL_H
#define JVM_CONSTANTPOOL_H
#include "util.h"
#include "ClassReader.h"
#include <map>

class ConstantInfo;

class ConstantIntegerInfo;

class ConstantFloatInfo;

class ConstantLongInfo;

class ConstantDoubleInfo;

class ConstantUtf8Info;

class ConstantStringInfo;

class ConstantClassInfo;

/**
 * class ConstantFieldrefInfo;
 *
 *class ConstantMethodrefInfo;
 *
 *class ConstantInterfaceMethodrefInfo;
*/

class ConstantMemberrefInfo;

class ConstantNameAndTypeInfo;

class ConstantMethodTypeInfo;

class ConstantMethodHandleInfo;

class ConstantInvokeDynamicInfo;

class ConstantPool;

class ConstantInfo
{
  public:
	virtual uint8_t getTag() = 0;
	virtual void readInfo(ClassReader *reader) = 0;
};

class ConstantIntegerInfo: public ConstantInfo
{
	int32_t value;
  public:
	explicit ConstantIntegerInfo() : value(0)
	{};
	uint8_t getTag() override;
	void readInfo(ClassReader *reader) override;
};

class ConstantFloatInfo: public ConstantInfo
{
	float value;
  public:
	explicit ConstantFloatInfo() : value(0)
	{};
	uint8_t getTag() override;
	void readInfo(ClassReader *reader) override;
};

class ConstantLongInfo: public ConstantInfo
{
	int64_t value;
  public:
	explicit ConstantLongInfo() : value(0)
	{};
	uint8_t getTag() override;
	void readInfo(ClassReader *reader) override;
};

class ConstantDoubleInfo: public ConstantInfo
{
	double value;
  public:
	explicit ConstantDoubleInfo() : value(0)
	{};
	uint8_t getTag() override;
	void readInfo(ClassReader *reader) override;
};

class ConstantUtf8Info: public ConstantInfo
{
  public:
	explicit ConstantUtf8Info() : value("")
	{};
	uint8_t getTag() override;
	void readInfo(ClassReader *reader) override;
	std::string value;
};

class ConstantStringInfo: public ConstantInfo
{
	ConstantPool *cp;
	uint16_t stringIndex;
  public:
	explicit ConstantStringInfo(ConstantPool *cp) : cp(cp), stringIndex(0)
	{};
	uint8_t getTag() override;
	void readInfo(ClassReader *reader) override;
	std::string String();
};

class ConstantClassInfo: public ConstantInfo
{
	ConstantPool *cp;
	uint16_t nameIndex;
  public:
	explicit ConstantClassInfo(ConstantPool *cp) : cp(cp), nameIndex(0)
	{};
	uint8_t getTag() override;
	void readInfo(ClassReader *reader) override;
	std::string Name();
};

class ConstantNameAndTypeInfo: public ConstantInfo
{
  public:
	explicit ConstantNameAndTypeInfo() : nameIndex(0), descriptorIndex(0)
	{};
	uint8_t getTag() override;
	void readInfo(ClassReader *reader) override;
	uint16_t nameIndex;
	uint16_t descriptorIndex;
};

class ConstantMethodHandleInfo: public ConstantInfo
{
	uint8_t referenceKind;
	uint16_t referenceIndex;
  public:
	explicit ConstantMethodHandleInfo() : referenceIndex(0), referenceKind(0)
	{}
	
	uint8_t getTag() override;
	void readInfo(ClassReader *reader) override;
};

class ConstantMethodTypeInfo: public ConstantInfo
{
	uint16_t descriptorIndex;
  public:
	explicit ConstantMethodTypeInfo() : descriptorIndex(0)
	{}
	
	uint8_t getTag() override;
	void readInfo(ClassReader *reader) override;
};

class ConstantInvokeDynamicInfo: public ConstantInfo
{
	uint16_t bootstrapMethodAttrIndex;
	uint16_t nameAndTypeIndex;
  public:
	explicit ConstantInvokeDynamicInfo() : bootstrapMethodAttrIndex(0), nameAndTypeIndex(0)
	{}
	
	uint8_t getTag() override;
	void readInfo(ClassReader *reader) override;
};

class ConstantMemberrefInfo: public ConstantInfo
{
	uint8_t tag;
	ConstantPool *cp;
	uint16_t classIndex;
	uint16_t nameAndTypeIndex;
  public:
	explicit ConstantMemberrefInfo(uint8_t tag, ConstantPool *cp) : tag(tag), cp(cp), classIndex(0), nameAndTypeIndex(0)
	{}
	
	uint8_t getTag() override;
	void readInfo(ClassReader *reader) override;
	std::string ClassName();
	std::map<std::string, std::string> NameAndType(uint16_t index);
};

namespace ConstantInfoSpace
{
	const uint8_t CONSTANT_Class = 7;
	const uint8_t CONSTANT_Fieldref = 9;
	const uint8_t CONSTANT_Methodref = 10;
	const uint8_t CONSTANT_InterfaceMethodref = 11;
	const uint8_t CONSTANT_String = 8;
	const uint8_t CONSTANT_Integer = 3;
	const uint8_t CONSTANT_Float = 4;
	const uint8_t CONSTANT_Long = 5;
	const uint8_t CONSTANT_Double = 6;
	const uint8_t CONSTANT_NameAndType = 12;
	const uint8_t CONSTANT_Utf8 = 1;
	const uint8_t CONSTANT_MethodHandle = 15;
	const uint8_t CONSTANT_MethodType = 16;
	const uint8_t CONSTANT_InvokeDynamic = 18;
	ConstantInfo *readConstantInfo(ClassReader *reader, ConstantPool *cp);
	ConstantInfo *newConstantInfo(uint8_t tag, ConstantPool *cp);
	std::string decodeMUTF8(std::vector<byte>);
}

class ConstantPool
{
  public:
	explicit ConstantPool(std::vector<ConstantInfo *> info) : Info(info)
	{}
	
	std::vector<ConstantInfo *> Info;
	static ConstantPool *readConstantPool(ClassReader *reader);
	ConstantInfo *getConstantInfo(uint16_t index);
	std::map<std::string, std::string> getNameAndType(uint16_t index);
	std::string getClassName(uint16_t index);
	std::string getUtf8(uint16_t index);
};

#endif //JVM_CONSTANTPOOL_H
