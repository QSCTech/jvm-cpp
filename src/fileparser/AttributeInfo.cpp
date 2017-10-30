//
// Created by 李晨曦 on 29/10/2017.
//

#include "AttributeInfo.h"

AttributeInfo *AttributeSpace::readAttribute(ClassReader *reader, ConstantPool *cp)
{
	auto attrNameIndex = reader->readUint16();
	auto attrName = cp->getUtf8(attrNameIndex);
	auto attrLen = reader->readUint32();
	auto attrInfo = newAttributeInfo(attrName, attrLen, cp);
	attrInfo->readInfo(reader);
	return attrInfo;
}

std::vector<AttributeInfo *> AttributeSpace::readAttributes(ClassReader *reader, ConstantPool *cp)
{
	auto attrCount = reader->readUint16();
	std::vector<AttributeInfo *> attributes(attrCount);
	for (int i = 0; i < attrCount; i++)
	{
		attributes[i] = readAttribute(reader, cp);
	}
	return attributes;
}

AttributeInfo *AttributeSpace::newAttributeInfo(std::string attrName, uint32_t attrLen, ConstantPool *cp)
{
	if (attrName == CodeATTR) return new CodeAttribute(attrName, cp);
	if (attrName == ConstantValueATTR) return new ConstantValueAttribute(attrName);
	if (attrName == DeprecatedATTR || attrName == SyntheticATTR) return new MarkerAttribute(attrName);
	if (attrName == ExceptionsATTR) return new ExceptionsAttribute(attrName);
	if (attrName == LineNumberTableATTR) return new LineNumberTableAttribute(attrName);
	if (attrName == LocalVariableTableATTR) return new LocalVariableTableAttribute(attrName);
	if (attrName == SourceFileATTR) return new SourceFileAttribute(attrName, cp);
	return new UnparsedAttribute(attrName, attrLen);
}

void UnparsedAttribute::readInfo(ClassReader *reader)
{
	this->info = reader->readBytes(this->length);
}

std::string UnparsedAttribute::getAttrName()
{
	return this->attrName;
}

void MarkerAttribute::readInfo(ClassReader *reader)
{}

std::string MarkerAttribute::getAttrName()
{
	return this->attrName;
}

void SourceFileAttribute::readInfo(ClassReader *reader)
{
	this->sourceFileIndex = reader->readUint16();
}

std::string SourceFileAttribute::getAttrName()
{
	return this->attrName;
}

std::string SourceFileAttribute::FileName()
{
	return this->cp->getUtf8(this->sourceFileIndex);
}

void ConstantValueAttribute::readInfo(ClassReader *reader)
{
	this->constantValueIndex = reader->readUint16();
}

std::string ConstantValueAttribute::getAttrName()
{
	return this->attrName;
}

uint16_t ConstantValueAttribute::ConstantValueIndex()
{
	return this->constantValueIndex;
}

void CodeAttribute::readInfo(ClassReader *reader)
{
	this->maxStack = reader->readUint16();
	this->maxLocals = reader->readUint16();
	auto codeLength = reader->readUint32();
	this->code = reader->readBytes(codeLength);
	this->readExceptionTable(reader);
	this->attributes = AttributeSpace::readAttributes(reader, this->cp);
}

std::string CodeAttribute::getAttrName()
{
	return this->attrName;
}

void CodeAttribute::readExceptionTable(ClassReader *reader)
{
	auto tableLength = reader->readUint16();
	this->exceptionTable = std::vector<ExceptionTableEntry *>(tableLength);
	for (int i = 0; i < this->exceptionTable.size(); i++)
	{
		this->exceptionTable[i] =
		new ExceptionTableEntry(reader->readUint16(), reader->readUint16(), reader->readUint16(), reader->readUint16());
	}
}

void ExceptionsAttribute::readInfo(ClassReader *reader)
{
	this->exceptionIndexTable = reader->readUint16s();
}

std::string ExceptionsAttribute::getAttrName()
{
	return this->attrName;
}

std::vector<uint16_t> ExceptionsAttribute::ExceptionIndexTable()
{
	return this->exceptionIndexTable;
}

void LineNumberTableAttribute::readInfo(ClassReader *reader)
{
	auto tableLen = reader->readUint16();
	this->lineNumberTable = std::vector<LineNumberTableEntry *>(tableLen);
	for (int i = 0; i < tableLen; i++)
	{
		this->lineNumberTable[i] = new LineNumberTableEntry(reader->readUint16(), reader->readUint16());
	}
}

std::string LineNumberTableAttribute::getAttrName()
{
	return this->attrName;
}

LocalVariableTableEntry::LocalVariableTableEntry(uint16_t startPc,
uint16_t length,
uint16_t nameIndex,
uint16_t descriptorIndex,
uint16_t index) : startPc(startPc), length(length), nameIndex(nameIndex), descriptorIndex(descriptorIndex), index(index)
{}

LocalVariableTableAttribute::LocalVariableTableAttribute(const std::string attrName) : attrName(attrName)
{}

std::string LocalVariableTableAttribute::getAttrName()
{
	return this->attrName;
}

void LocalVariableTableAttribute::readInfo(ClassReader *reader)
{
	auto tableLen = reader->readUint16();
	this->localVariableTable = std::vector<LocalVariableTableEntry *>(tableLen);
	for (int i = 0; i < tableLen; i++)
	{
		this->localVariableTable[i] = new LocalVariableTableEntry(reader->readUint16(),
		                                                          reader->readUint16(),
		                                                          reader->readUint16(),
		                                                          reader->readUint16(),
		                                                          reader->readUint16());
	}
}

