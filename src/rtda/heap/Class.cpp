//
// Created by 李晨曦 on 11/12/2017.
//

#include "Class.hpp"

Class::Class(ClassFile *cf)
: accessFlag(cf->AccessFlags()), name(cf->ClassName()), superClassName(cf->SuperClassName()),
  interfaceNames(cf->InterfaceName()),
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
