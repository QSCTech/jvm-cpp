//
// Created by 李晨曦 on 03/01/2018.
//

#ifndef JVM_RUNTIMECONSTANTPOOL_HPP
#define JVM_RUNTIMECONSTANTPOOL_HPP
#include "Class.hpp"
#include <boost/any.hpp>

class RunTimeConstantPool;

using Constant = boost::any ;

class SymRef;

class ClassRef;

class MemberRef;

class FieldRef;

class MethodRef;

class InterfaceMethodRef;

class RunTimeConstantPool
{
	Class *belongClass;
	std::vector<Constant> consts;
  public:
	RunTimeConstantPool(Class *belongClass, ConstantPool constPool);
	Constant getConstant(uint32_t index);
};

class SymRef
{
	RunTimeConstantPool *rtcp;
	std::string className;
	Class *ownClass;
  public:
	SymRef(RunTimeConstantPool *rtcp, std::string className, Class *ownClass);
};

class ClassRef: public SymRef
{
  public:
	ClassRef(RunTimeConstantPool *rtcp, ConstantClassInfo * classInfo);
};

class MemberRef: public SymRef
{
	std::string name;
	std::string description;
  public:
	MemberRef(RunTimeConstantPool *rtcp, ConstantMemberrefInfo* redInfo);
};

class FieldRef: public MemberRef
{
	Field *field;
  public:
	FieldRef(RunTimeConstantPool *rtcp, ConstantMemberrefInfo *redInfo);
};

class MethodRef: public MemberRef
{
	Method *method;
  public:
	MethodRef(RunTimeConstantPool *rtcp, ConstantMemberrefInfo *redInfo);
};

class InterfaceMethodRef: public MemberRef
{
	Method *method;
  public:
	InterfaceMethodRef(RunTimeConstantPool *rtcp, ConstantMemberrefInfo *redInfo);
};

#endif //JVM_RUNTIMECONSTANTPOOL_HPP
