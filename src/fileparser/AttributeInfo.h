//
// Created by 李晨曦 on 29/10/2017.
//

#ifndef JVM_ATTRIBUTEINFO_H
#define JVM_ATTRIBUTEINFO_H
#include "ClassReader.h"
#include "ConstantPool.h"
#include <vector>

/*
attribute_info {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 info[attribute_length];
}
*/
class AttributeInfo;

/*
Code_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 code[code_length];
    u2 exception_table_length;
    {   u2 start_pc;
        u2 end_pc;
        u2 handler_pc;
        u2 catch_type;
    } exception_table[exception_table_length];
    u2 attributes_count;
    attribute_info attributes[attributes_count];
}
*/
class CodeAttribute;

class ExceptionTableEntry;

class ConstantValueAttribute;

/*
Exceptions_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_exceptions;
    u2 exception_index_table[number_of_exceptions];
}
*/
class ExceptionsAttribute;

/*
LineNumberTable_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 line_number_table_length;
    {   u2 start_pc;
        u2 line_number;
    } line_number_table[line_number_table_length];
}
*/
class LineNumberTableAttribute;

class LineNumberTableEntry;

/*
LocalVariableTable_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 local_variable_table_length;
    {   u2 start_pc;
        u2 length;
        u2 name_index;
        u2 descriptor_index;
        u2 index;
    } local_variable_table[local_variable_table_length];
}
 */
class LocalVariableTableAttribute;

class LocalVariableTableEntry;

class SourceFileAttribute;

//class DeprecatedAttribute;
//
//class SyntheticAttribute;

class MarkerAttribute;

class UnparsedAttribute;

namespace AttributeSpace
{
	const std::string CodeATTR = "Code";
	const std::string ConstantValueATTR = "ConstantValue";
	const std::string DeprecatedATTR = "Deprecated";
	const std::string ExceptionsATTR = "Exceptions";
	const std::string LineNumberTableATTR = "LineNumberTable";
	const std::string LocalVariableTableATTR = "LocalVariableTable";
	const std::string SourceFileATTR = "SourceFile";
	const std::string SyntheticATTR = "Synthetic";
	const std::string UnparsedATTR = "Unparsed";
	std::vector<AttributeInfo *> readAttributes(ClassReader *reader, ConstantPool *cp);
	AttributeInfo *readAttribute(ClassReader *reader, ConstantPool *cp);
	AttributeInfo *newAttributeInfo(std::string attrName, uint32_t attrLen, ConstantPool *cp);
}

class AttributeInfo
{
  public:
	virtual void readInfo(ClassReader *reader) = 0;
	virtual std::string getAttrName() = 0;
};

class UnparsedAttribute: public AttributeInfo
{
	std::string attrName;
	uint32_t length;
	std::vector<byte> info;
  public:
	UnparsedAttribute(std::string attrName, uint32_t attrLen) : attrName(attrName), length(attrLen), info(std::vector<byte>())
	{}
	
	void readInfo(ClassReader *reader) override;
	std::string getAttrName() override;
};

class MarkerAttribute: public AttributeInfo
{
	std::string attrName;
  public:
	explicit MarkerAttribute(std::string attrName) : attrName(attrName)
	{}
	
	void readInfo(ClassReader *reader) override;
	std::string getAttrName() override;
};

class SourceFileAttribute: public AttributeInfo
{
	std::string attrName;
	ConstantPool *cp;
	uint16_t sourceFileIndex;
  public:
	SourceFileAttribute(std::string attrName, ConstantPool *cp) : attrName(attrName), cp(cp), sourceFileIndex(0)
	{}
	
	void readInfo(ClassReader *reader) override;
	std::string getAttrName() override;
	std::string FileName();
};

class ConstantValueAttribute: public AttributeInfo
{
	std::string attrName;
	uint16_t constantValueIndex;
  public:
	explicit ConstantValueAttribute(std::string attrName) : attrName(attrName), constantValueIndex(0)
	{}
	
	void readInfo(ClassReader *reader) override;
	std::string getAttrName() override;
	uint16_t ConstantValueIndex();
};

class CodeAttribute: public AttributeInfo
{
	std::string attrName;
	ConstantPool *cp;
	uint16_t maxStack;
	uint16_t maxLocals;
  public:
	uint16_t getMaxStack() const;
	uint16_t getMaxLocals() const;
	std::vector<uint8_t> getCode() const;
  private:
	std::vector<byte> code;
	std::vector<ExceptionTableEntry *> exceptionTable;
	std::vector<AttributeInfo *> attributes;
  public:
	CodeAttribute(std::string attrName, ConstantPool *cp) : attrName(attrName), cp(cp), maxStack(0), maxLocals(0)
	{}
	
	void readInfo(ClassReader *reader) override;
	std::string getAttrName() override;
	void readExceptionTable(ClassReader *classReader);
};

inline uint16_t CodeAttribute::getMaxStack() const
{
	return maxStack;
}

inline uint16_t CodeAttribute::getMaxLocals() const
{
	return maxLocals;
}

inline std::vector<uint8_t> CodeAttribute::getCode() const
{
	return code;
}

class ExceptionTableEntry
{
	uint16_t startPc;
	uint16_t endPc;
	uint16_t handlerPc;
	uint16_t catchType;
  public:
	ExceptionTableEntry(uint16_t startPc,
	uint16_t endPc,
	uint16_t handlerPc,
	uint16_t catchType) : startPc(startPc), endPc(endPc), handlerPc(handlerPc), catchType(catchType)
	{}
};

class ExceptionsAttribute: public AttributeInfo
{
	std::string attrName;
	std::vector<uint16_t> exceptionIndexTable;
  public:
	explicit ExceptionsAttribute(std::string attrName) : attrName(attrName)
	{}
	
	void readInfo(ClassReader *reader) override;
	std::string getAttrName() override;
	std::vector<uint16_t> ExceptionIndexTable();
};


class LineNumberTableAttribute: public AttributeInfo
{
	std::string attrName;
	std::vector<LineNumberTableEntry *> lineNumberTable;
  public:
	explicit LineNumberTableAttribute(std::string attrName) : attrName(attrName)
	{}
	void readInfo(ClassReader *reader) override;
	std::string getAttrName() override;
};

class LineNumberTableEntry
{
	uint16_t startPc;
	uint16_t lineNumber;
  public:
	LineNumberTableEntry(uint16_t startPc,
	uint16_t lineNumber): startPc(startPc), lineNumber(lineNumber){}
};

class LocalVariableTableAttribute: public AttributeInfo
{
	std::string attrName;
	std::vector<LocalVariableTableEntry *> localVariableTable;
  public:
	explicit LocalVariableTableAttribute(std::string attrName);
	std::string getAttrName() override ;
	void readInfo(ClassReader *reader) override;
};

class LocalVariableTableEntry
{
	uint16_t startPc;
	uint16_t length;
	uint16_t nameIndex;
	uint16_t descriptorIndex;
	uint16_t index;
  public:
	LocalVariableTableEntry(uint16_t startPc,
	uint16_t length,
	uint16_t nameIndex,
	uint16_t descriptorIndex,
	uint16_t index);
};

#endif //JVM_ATTRIBUTEINFO_H
