////
//// Created by 李晨曦 on 03/01/2018.
////
//
//#include "RunTimeConstantPool.hpp"
//
//RunTimeConstantPool::RunTimeConstantPool(Class *belongClass, ConstantPool constPool) : belongClass(
//belongClass), consts(std::vector<Constant>(constPool.Info.size()))
//{
//	using namespace ConstantInfoSpace;
//	for (auto constInfo: constPool.Info)
//	{
//		if (constInfo == nullptr)
//		{
//			continue;
//		}
//		switch (constInfo->getTag())
//		{
//			case CONSTANT_Integer:
//				consts.emplace_back(((ConstantIntegerInfo *) (constInfo))->getValue());
//			case CONSTANT_Float:
//				consts.emplace_back(((ConstantFloatInfo *) (constInfo))->getValue());
//			case CONSTANT_Long:
//				consts.emplace_back(((ConstantLongInfo *) (constInfo))->getValue());
//			case CONSTANT_Double:
//				consts.emplace_back(((ConstantDoubleInfo *) (constInfo))->getValue());
//			case CONSTANT_String:
//				consts.emplace_back(((ConstantStringInfo*)(constInfo))->String());
//			case CONSTANT_Class:
//				consts.emplace_back(ClassRef(this, ((ConstantClassInfo*)(constInfo))));
//			case CONSTANT_Fieldref:
//				consts.emplace_back(FieldRef(this, ((ConstantFieldrefInfo *)(constInfo))));
//			case CONSTANT_Methodref:
//				consts.emplace_back(MemberRef(this, ((ConstantMethodrefInfo *)(constInfo))));
//			case CONSTANT_InterfaceMethodref:
//				consts.emplace_back(InterfaceMethodRef(this, ((ConstantInterfaceMethodrefInfo *)(constInfo))));
//			default:
//				break;
//		}
//	}
//}
//
//SymRef::SymRef(RunTimeConstantPool *rtcp, std::string className, Class *ownClass)
//: rtcp(rtcp), className(className), ownClass(ownClass)
//{}
//
//
//Constant RunTimeConstantPool::getConstant(uint32_t index)
//{
//	return Constant();
//}
//
//ClassRef::ClassRef(RunTimeConstantPool *rtcp, ConstantClassInfo * classInfo) : SymRef(rtcp, classInfo->Name(), nullptr)
//{}
//
//MemberRef::MemberRef(RunTimeConstantPool *rtcp, ConstantMemberrefInfo *readInfo) : SymRef(
//rtcp,
//readInfo->ClassName(),
//nullptr), name(readInfo->NameAndType()["name"]), description(readInfo->NameAndType()["type"])
//{}
//
//FieldRef::FieldRef(RunTimeConstantPool *rtcp,
//ConstantFieldrefInfo *redInfo) : MemberRef(rtcp, redInfo), field(nullptr)
//{}
//
//MethodRef::MethodRef(RunTimeConstantPool *rtcp, ConstantMethodrefInfo *redInfo)
//: MemberRef(rtcp, redInfo), method(nullptr)
//{}
//
//InterfaceMethodRef::InterfaceMethodRef(RunTimeConstantPool *rtcp, ConstantInterfaceMethodrefInfo *redInfo)
//: MemberRef(rtcp, redInfo), method(nullptr)
//{}
