//
// Created by 李晨曦 on 27/10/2017.
//
#include "ClassFile.h"

ParseResult ClassFile::Parse(std::vector<BYTE> classData)
{
	try
	{
		auto cr = ClassReader(classData);
		auto result = this->Read(&cr);
		return result;
	} catch (std::exception &e)
	{
		return {std::string(e.what()), STATUS_ERR};
	}
}

ParseResult ClassFile::Read(ClassReader *reader)
{
	auto result = this->readAndCheckMagic(reader);
	if (result.status == STATUS_ERR)
	{
		return result;
	}
	result = this->readAndCheckVersion(reader);
	if (result.status == STATUS_ERR)
	{
		return result;
	}
	this->cp = ConstantPool::readConstantPool(reader);
	this->accessFlags = reader->readUint16();
	this->thisClass = reader->readUint16();
	this->superClass = reader->readUint16();
	this->interfaces = reader->readUint16s();
	this->fields = MemberInfo::readMembers(reader, this->cp);
	this->methods = MemberInfo::readMembers(reader, this->cp);
	this->attributes = AttributeInfo::readAttributes(reader, this->cp);
	return {"", STATUS_OK};
}

ParseResult ClassFile::readAndCheckMagic(ClassReader *reader)
{
	this->magic = reader->readUint32();
	if (magic != 0xCAFEBABE)
	{
		return {"java.lang.ClassFormatError: magic!", STATUS_ERR};
	}
	return {"", STATUS_OK};
}

ParseResult ClassFile::readAndCheckVersion(ClassReader *reader)
{
	this->minorVersion = reader->readUint16();
	this->majorVersion = reader->readUint16();
	if (this->majorVersion == 45) return {"", STATUS_OK};
	if (this->majorVersion > 45 && this->majorVersion <= 52 && this->minorVersion == 0) return {"", STATUS_OK};
	return {"java.lang.UnsupportedClassVersionError!", STATUS_ERR};
}

uint16_t ClassFile::MinorVersion()
{
	return this->minorVersion;
}

uint16_t ClassFile::MajorVersion()
{
	return this->majorVersion;
}

ConstantPool *ClassFile::GetConstantPool()
{
	return this->cp;
}

uint16_t ClassFile::AccessFlags()
{
	return this->accessFlags;
}

std::vector<MemberInfo *> ClassFile::Fields()
{
	return this->fields;
}

std::vector<MemberInfo *> ClassFile::Methods()
{
	return this->methods;
}

std::string ClassFile::ClassName()
{
	return this->cp->getClassName(this->thisClass);
}

std::string ClassFile::SuperClassName()
{
	if (this->superClass > 0) return this->cp->getClassName(this->superClass);
	return ""; /* java.lang.Object don't has superclass */
}

std::vector<std::string> ClassFile::InterfaceName()
{
	std::vector<std::string> vec(this->interfaces.size());
	for (int i = 0; i < vec.size(); i++)
	{
		vec[i] = this->cp->getClassName(this->interfaces[i]);
	}
	return vec;
}


std::vector<MemberInfo *> MemberInfo::readMembers(ClassReader *reader, ConstantPool *constantPool)
{
	auto memberCount = reader->readUint16();
	std::vector<MemberInfo *> members(memberCount);
	for (int i = 0; i < memberCount; i++)
	{
		members[i] = readMember(reader, constantPool);
	}
	return members;
}

MemberInfo *MemberInfo::readMember(ClassReader *reader, ConstantPool *constantPool)
{
	return new MemberInfo(constantPool,
	                      reader->readUint16(),
	                      reader->readUint16(),
	                      reader->readUint16(),
	                      AttributeInfo::readAttributes(reader, constantPool));
}

uint16_t MemberInfo::AccessFlags()
{
	return this->accessFlags;
}

std::string MemberInfo::Name()
{
	return this->constantPool->getUtf8(this->nameIndex);
}

std::string MemberInfo::Descriptor()
{
	return this->constantPool->getUtf8(this->descriptorIndex);
}

ConstantInfo *ConstantInfoSpace::newConstantInfo(uint8_t tag, ConstantPool *cp)
{
	switch (tag)
	{
		case CONSTANT_Integer:
			return new ConstantIntegerInfo();
		case CONSTANT_Float:
			return new ConstantFloatInfo();
		case CONSTANT_Double:
			return new ConstantDoubleInfo();
		case CONSTANT_Long:
			return new ConstantLongInfo();
		case CONSTANT_Utf8:
			return new ConstantUtf8Info();
		case CONSTANT_String:
			return new ConstantStringInfo(cp);
		case CONSTANT_Class:
			return new ConstantClassInfo(cp);
		case CONSTANT_Fieldref:
		case CONSTANT_Methodref:
		case CONSTANT_InterfaceMethodref:
			return new ConstantMemberrefInfo(tag, cp);
		case CONSTANT_NameAndType:
			return new ConstantNameAndTypeInfo();
		case CONSTANT_MethodType:
			return new ConstantMethodTypeInfo();
		case CONSTANT_MethodHandle:
			return new ConstantMethodHandleInfo();
		case CONSTANT_InvokeDynamic:
			return new ConstantInvokeDynamicInfo();
		default:
			throw JavaClassFormatError("constant pool tag!");
	}
}

ConstantInfo *ConstantInfoSpace::readConstantInfo(ClassReader *reader, ConstantPool *cp)
{
	auto tag = reader->readUint8();
	auto constant = newConstantInfo(tag, cp);
	constant->readInfo(reader);
	return constant;
}

ConstantPool *ConstantPool::readConstantPool(ClassReader *reader)
{
	auto cpCount = reader->readUint16();
	auto cp = new ConstantPool(std::vector<ConstantInfo *>(cpCount));
	cp->Info[0] = nullptr;
	for (uint16_t i = 1; i < cpCount; i++)
	{
		cp->Info[i] = ConstantInfoSpace::readConstantInfo(reader, cp);
		switch (cp->Info[i]->getTag())
		{
			case ConstantInfoSpace::CONSTANT_Long:
			case ConstantInfoSpace::CONSTANT_Double:
				cp->Info[++i] = nullptr;
				break;
			default:
				break;
		}
	}
	return cp;
}

ConstantInfo *ConstantPool::getConstantInfo(uint16_t index)
{
	if (index < this->Info.size() && index > 0)
	{
		auto cpInfo = this->Info[index];
		if (cpInfo != nullptr)
		{
			return cpInfo;
		}
	}
	throw ConstantPoolIndexInvalid();
}

std::map<std::string, std::string> ConstantPool::getNameAndType(uint16_t index)
{
	std::map<std::string, std::string> result;
	auto info = (ConstantNameAndTypeInfo *) this->getConstantInfo(index);
	result["name"] = this->getUtf8(info->nameIndex);
	result["type"] = this->getUtf8(info->descriptorIndex);
	return result;
};

std::string ConstantPool::getClassName(uint16_t index)
{
	auto info = (ConstantClassInfo *) this->getConstantInfo(index);
	return info->Name();
}

std::string ConstantPool::getUtf8(uint16_t index)
{
	auto info = (ConstantUtf8Info *) this->getConstantInfo(index);
	return info->value;
}

uint8_t ConstantIntegerInfo::getTag()
{
	return ConstantInfoSpace::CONSTANT_Integer;
}

void ConstantIntegerInfo::readInfo(ClassReader *reader)
{
	this->value = (int32_t) reader->readUint32();
}

uint8_t ConstantFloatInfo::getTag()
{
	return ConstantInfoSpace::CONSTANT_Float;
}

void ConstantFloatInfo::readInfo(ClassReader *reader)
{
	this->value = (float) reader->readUint32();
}

uint8_t ConstantLongInfo::getTag()
{
	return ConstantInfoSpace::CONSTANT_Long;
}

void ConstantLongInfo::readInfo(ClassReader *reader)
{
	this->value = (int64_t) reader->readUint64();
}

uint8_t ConstantDoubleInfo::getTag()
{
	return ConstantInfoSpace::CONSTANT_Double;
}

void ConstantDoubleInfo::readInfo(ClassReader *reader)
{
	this->value = (double) reader->readUint64();
}

uint8_t ConstantUtf8Info::getTag()
{
	return ConstantInfoSpace::CONSTANT_Utf8;
}

std::string ConstantInfoSpace::decodeMUTF8(std::vector<BYTE> bytes)
{
	return std::string(bytes.begin(), bytes.end());
}

void ConstantUtf8Info::readInfo(ClassReader *reader)
{
	uint32_t length = reader->readUint16();
	auto bytes = reader->readBytes(length);
	this->value = ConstantInfoSpace::decodeMUTF8(bytes);
}

uint8_t ConstantStringInfo::getTag()
{
	return ConstantInfoSpace::CONSTANT_String;
}

void ConstantStringInfo::readInfo(ClassReader *reader)
{
	this->stringIndex = reader->readUint16();
}

std::string ConstantStringInfo::String()
{
	return this->cp->getUtf8(this->stringIndex);
}

uint8_t ConstantClassInfo::getTag()
{
	return ConstantInfoSpace::CONSTANT_Class;
}

void ConstantClassInfo::readInfo(ClassReader *reader)
{
	this->nameIndex = reader->readUint16();
}

std::string ConstantClassInfo::Name()
{
	return this->cp->getUtf8(this->nameIndex);
}

uint8_t ConstantNameAndTypeInfo::getTag()
{
	return ConstantInfoSpace::CONSTANT_NameAndType;
}

void ConstantNameAndTypeInfo::readInfo(ClassReader *reader)
{
	this->nameIndex = reader->readUint16();
	this->descriptorIndex = reader->readUint16();
}

uint8_t ConstantMemberrefInfo::getTag()
{
	return this->tag;
}

void ConstantMemberrefInfo::readInfo(ClassReader *reader)
{
	this->classIndex = reader->readUint16();
	this->nameAndTypeIndex = reader->readUint16();
}

std::string ConstantMemberrefInfo::ClassName()
{
	return this->cp->getClassName(this->classIndex);
}

std::map<std::string, std::string> ConstantMemberrefInfo::NameAndType(uint16_t index)
{
	return this->cp->getNameAndType(this->nameAndTypeIndex);
};

uint8_t ConstantMethodHandleInfo::getTag()
{
	return ConstantInfoSpace::CONSTANT_MethodHandle;
}

void ConstantMethodHandleInfo::readInfo(ClassReader *reader)
{
	this->referenceKind = reader->readUint8();
	this->referenceIndex = reader->readUint16();
}

uint8_t ConstantMethodTypeInfo::getTag()
{
	return ConstantInfoSpace::CONSTANT_MethodType;
}

void ConstantMethodTypeInfo::readInfo(ClassReader *reader)
{
	this->descriptorIndex = reader->readUint16();
}

uint8_t ConstantInvokeDynamicInfo::getTag()
{
	return ConstantInfoSpace::CONSTANT_InvokeDynamic;
}

void ConstantInvokeDynamicInfo::readInfo(ClassReader *reader)
{
	this->bootstrapMethodAttrIndex = reader->readUint16();
	this->nameAndTypeIndex = reader->readUint16();
}

std::vector<AttributeInfo> AttributeInfo::readAttributes(ClassReader *reader, ConstantPool *cp)
{

}