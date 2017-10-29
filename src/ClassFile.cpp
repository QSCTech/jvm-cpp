#include "ClassFile.h"

ParseResult ClassFile::Parse(std::vector<byte> classData)
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
	try
	{
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
	catch (JavaClassFormatError &err)
	{
		return {std::string(err.what()), STATUS_ERR};
	}
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
	return {"java.lang.UnsupportedClassVersionError!: major: " + std::to_string(this->majorVersion), STATUS_ERR};
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

std::vector<AttributeInfo> AttributeInfo::readAttributes(ClassReader *reader, ConstantPool *cp)
{

}