//
// Created by 李晨曦 on 11/12/2017.
//

#ifndef JVM_CLASS_HPP
#define JVM_CLASS_HPP
#include <cstdint>
#include <string>
#include <vector>
#include <boost/any.hpp>
#include "classpath.hpp"
#include "ClassFile.hpp"
#include "AccessFlags.hpp"

class Class;

class RunTimeConstantPool;

using Constant = boost::any;

class SymRef;

class ClassRef;

class MemberRef;

class FieldRef;

class MethodRef;

class InterfaceMethodRef;

class ClassMember;

class Field;

class Method;

class ClassLoader;

class Object;

union DoubleUnion;

union Slot;

class LocalVars;

extern std::string ObjectClass;

extern std::vector<std::string> IntTypesStr;

extern std::vector<byte> IntTypesByte;

class Class {
	uint16_t accessFlag;
	std::string name;
	std::string superClassName;
	std::vector<std::string> interfaceNames;
	RunTimeConstantPool *constantPool;
	std::vector<Field *> fields;
	std::vector<Method *> methods;
	ClassLoader *loader;
	Class *superClass;
	std::vector<Class *> interfaces;
	uint32_t instanceSlotCount;
	uint32_t staticSlotCount;
	LocalVars *staticVars;
	template<class T>
	std::vector<T *> load(std::vector<MemberInfo *>);
  public:
	uint16_t getAccessFlag() const;
	const std::string &getSuperClassName() const;
	const std::vector<std::string> &getInterfaceNames() const;
	RunTimeConstantPool *getConstantPool() const;
	void setStaticSlotCount(uint32_t staticSlotCount);
	const std::vector<Field *> &getFields() const;
	const std::vector<Method *> &getMethods() const;
	ClassLoader *getLoader() const;
	Class *getSuperClass() const;
	const std::vector<Class *> &getInterfaces() const;
	void setStaticVars(LocalVars *staticVars);
	uint32_t getInstanceSlotCount() const;
	void setInstanceSlotCount(uint32_t instanceSlotCount);
	void setSuperClass(Class *superClass);
	uint32_t getStaticSlotCount() const;
	void setInterfaces(const std::vector<Class *> &interfaces);
	LocalVars *getStaticVars() const;
	void setLoader(ClassLoader *loader);
	const std::string &getName() const;
	std::string getPackageName();
	explicit Class(ClassFile *cf);
	Method* getStaticMethod(std::string name, std::string descriptor);
	Method* getMainMethod();
	bool IsPublic();
	bool IsSuper();
	bool IsInterface();
	bool IsAbstract();
	bool IsFinal();
	bool IsSynthetic();
	bool IsEnum();
	bool IsAnnotition();
	bool IsAccessibleTo(Class *);
	bool IsSubClassOf(Class *otherClass);
	
};

class RunTimeConstantPool {
	std::vector<Constant> consts;
  public:
	Class *belongClass;
	RunTimeConstantPool(Class *belongClass, ConstantPool constPool);
	Constant getConstant(uint32_t index);
};

class SymRef {
	void resolveClassRef();
  public:
	std::string className;
	RunTimeConstantPool *rtcp;
	Class *ownClass;
	SymRef(RunTimeConstantPool *rtcp, std::string className, Class *ownClass);
	Class *ResolveClass();
};

class ClassRef: public SymRef {
  public:
	ClassRef(RunTimeConstantPool *rtcp, ConstantClassInfo *classInfo);
};

class MemberRef: public SymRef {
  public:
	std::string name;
	std::string description;
	MemberRef(RunTimeConstantPool *rtcp, ConstantMemberrefInfo *redInfo);
};

class FieldRef: public MemberRef {
	Field *field;
  public:
	FieldRef(RunTimeConstantPool *rtcp, ConstantMemberrefInfo *redInfo);
	Field* ResolveField();
	void resolveFieldRef();
	static Field* lookupField(Class* owner, std::string name, std::string descriptor);
};

class MethodRef: public MemberRef {
	Method *method;
  public:
	MethodRef(RunTimeConstantPool *rtcp, ConstantMemberrefInfo *redInfo);
};

class InterfaceMethodRef: public MemberRef {
	Method *method;
  public:
	InterfaceMethodRef(RunTimeConstantPool *rtcp, ConstantMemberrefInfo *redInfo);
};

class ClassMember {
  public:
	uint16_t accessFlags;
	std::string name;
	std::string descriptor;
	Class *belongClass;
	ClassMember(MemberInfo *memberInfo, Class *belongClass);
	bool IsAccessibleTo(Class *otherClass);
	bool IsPublic();
	bool IsStatic();
	bool IsProtected();
	bool IsPrivate();
	bool IsFinal();
};

class Field: public ClassMember {
  public:
	uint32_t constValueIndex;
	uint32_t slotId;
	Field(MemberInfo *memberInfo, Class *belongClass);
	bool IsSynthetic();
	bool IsTransient();
	bool IsEnum();
	bool IsVolatile();
	bool IsLongOrDouble();
};

class Method: public ClassMember {
  public:
	std::vector<byte> code;
	uint32_t maxStack;
	uint32_t maxLocals;
	Method(MemberInfo *memberInfo,
	Class *belongClass);
	bool IsSynthetic();
	bool IsAbstract();
	bool IsSynchronized();
	bool IsBridge();
	bool IsVarargs();
	bool IsNative();
	bool IsStrict();
};


class ClassLoader {
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
	static void initStaticFinalVar(Class *newClass, Field *field);
};

union DoubleUnion {
	double value;
	int32_t storage[2];
};

union Slot {
  public:
	int32_t num;
	Object *ref;
	explicit Slot(int32_t num);
	explicit Slot(Object *ref);
};

class LocalVars {
  public:
	std::vector<Slot *> slots;
	explicit LocalVars(uint32_t maxLocals);
	void SetInt(uint32_t index, int32_t val);
	int32_t GetInt(uint32_t index);
	void SetFloat(uint32_t index, float val);
	float GetFloat(uint32_t index);
	void SetLong(uint32_t index, int64_t val);
	int64_t GetLong(uint32_t index);
	void SetDouble(uint32_t index, double val);
	double GetDouble(uint32_t index);
	void SetRef(uint32_t index, Object *ref);
	Object *GetRef(uint32_t index);
};

class Object {
  public:
	Class *ownClass;
	LocalVars *fields;
	Object(Class *ownClass);
};

inline void LocalVars::SetInt(uint32_t index, int32_t val) {
	this->slots[index]->num = val;
}

inline int32_t LocalVars::GetInt(uint32_t index) {
	return this->slots[index]->num;
}

inline void LocalVars::SetFloat(uint32_t index, float val) {
	this->slots[index]->num = *(int *) (&val);
}

inline float LocalVars::GetFloat(uint32_t index) {
	return *(float *) &(this->slots[index]->num);
}

inline void LocalVars::SetLong(uint32_t index, int64_t val) {
	this->slots[index]->num = (int32_t) val;
	this->slots[index + 1]->num = (int32_t) (val >> 32);
}

inline int64_t LocalVars::GetLong(uint32_t index) {
	auto low = (int64_t) (this->slots[index]->num);
	auto high = (int64_t) (this->slots[index + 1]->num);
	return high << 32 | low;
}

inline void LocalVars::SetDouble(uint32_t index, double val) {
	DoubleUnion DU = {val};
	this->SetInt(index, DU.storage[0]);
	this->SetInt(index + 1, DU.storage[1]);
}

inline double LocalVars::GetDouble(uint32_t index) {
	DoubleUnion DU = {};
	DU.storage[0] = this->GetInt(index);
	DU.storage[1] = this->GetInt(index + 1);
	return DU.value;
}

inline void LocalVars::SetRef(uint32_t index, Object *ref) {
	this->slots[index]->ref = ref;
}

inline Object *LocalVars::GetRef(uint32_t index) {
	return this->slots[index]->ref;
}


inline bool Class::IsPublic() {
	return 0 != (accessFlag & AccessFlags::ACC_PUBLIC);
}

inline bool Class::IsFinal() {
	return 0 != (accessFlag & AccessFlags::ACC_FINAL);
}

inline bool Class::IsSuper() {
	return 0 != (accessFlag & AccessFlags::ACC_SUPER);
}

inline bool Class::IsInterface() {
	return 0 != (accessFlag & AccessFlags::ACC_INTERFACE);
}

inline bool Class::IsAbstract() {
	return 0 != (accessFlag & AccessFlags::ACC_ABSTRACT);
}

inline bool Class::IsSynthetic() {
	return 0 != (accessFlag & AccessFlags::ACC_SYNTHETIC);
}

inline bool Class::IsAnnotition() {
	return 0 != (accessFlag & AccessFlags::ACC_ANNOTATION);
}

inline bool Class::IsEnum() {
	return 0 != (accessFlag & AccessFlags::ACC_ENUM);
}

template<class T>
std::vector<T *> Class::load(std::vector<MemberInfo *> membersInfos) {
	auto results = std::vector<T *>();
	for (auto memberInfo : membersInfos) {
		results.push_back(new T(memberInfo, this));
	}
	return results;
}

inline const std::string &Class::getName() const {
	return name;
}

inline void Class::setSuperClass(Class *superClass) {
	Class::superClass = superClass;
}

inline uint16_t Class::getAccessFlag() const {
	return accessFlag;
}

inline const std::string &Class::getSuperClassName() const {
	return superClassName;
}

inline const std::vector<std::string> &Class::getInterfaceNames() const {
	return interfaceNames;
}

inline RunTimeConstantPool *Class::getConstantPool() const {
	return constantPool;
}

inline const std::vector<Field *> &Class::getFields() const {
	return fields;
}

inline const std::vector<Method *> &Class::getMethods() const {
	return methods;
}

inline ClassLoader *Class::getLoader() const {
	return loader;
}

inline Class *Class::getSuperClass() const {
	return superClass;
}

inline const std::vector<Class *> &Class::getInterfaces() const {
	return interfaces;
}

inline uint32_t Class::getInstanceSlotCount() const {
	return instanceSlotCount;
}

inline uint32_t Class::getStaticSlotCount() const {
	return staticSlotCount;
}

inline LocalVars *Class::getStaticVars() const {
	return staticVars;
}

inline void Class::setInterfaces(const std::vector<Class *> &interfaces) {
	Class::interfaces = interfaces;
}

inline void Class::setLoader(ClassLoader *loader) {
	Class::loader = loader;
}

inline void Class::setInstanceSlotCount(uint32_t instanceSlotCount) {
	Class::instanceSlotCount = instanceSlotCount;
}

inline void Class::setStaticSlotCount(uint32_t staticSlotCount) {
	Class::staticSlotCount = staticSlotCount;
}

inline void Class::setStaticVars(LocalVars *staticVars) {
	Class::staticVars = staticVars;
}

inline bool Class::IsAccessibleTo(Class *otherClass) {
	return IsPublic() || getPackageName() == otherClass->getPackageName();
}

inline std::string Class::getPackageName() {
	auto position = name.find_last_of('/');
	if (position != std::string::npos) {
		return name.substr(0, position);
	}
	return "";
}

inline Method *Class::getStaticMethod(std::string name, std::string descriptor) {
	for (auto method : methods) {
		if (method->IsStatic() && method->name == name && method->descriptor == descriptor) {
			return method;
		}
	}
	return nullptr;
}

inline Method *Class::getMainMethod() {
	return getStaticMethod("main", "([Ljava/lang/String;)V");
}

inline bool ClassMember::IsPublic() {
	return (accessFlags & AccessFlags::ACC_PUBLIC) != 0;
}

inline bool ClassMember::IsStatic() {
	return (accessFlags & AccessFlags::ACC_STATIC) != 0;
}

inline bool ClassMember::IsProtected() {
	return (accessFlags & AccessFlags::ACC_PROTECTED) != 0;
}

inline bool ClassMember::IsPrivate() {
	return (accessFlags & AccessFlags::ACC_PRIVATE) != 0;
}

inline bool ClassMember::IsFinal() {
	return (accessFlags & AccessFlags::ACC_FINAL) != 0;
}

inline bool Field::IsTransient() {
	return (accessFlags & AccessFlags::ACC_TRANSIENT) != 0;
}

inline bool Field::IsSynthetic() {
	return (accessFlags & AccessFlags::ACC_SYNTHETIC) != 0;
}

inline bool Field::IsEnum() {
	return (accessFlags & AccessFlags::ACC_ENUM) != 0;
}

inline bool Field::IsVolatile() {
	return (accessFlags & AccessFlags::ACC_VOLATILE) != 0;
}

inline bool Field::IsLongOrDouble() {
	return descriptor == "J" || descriptor == "D";
}

inline bool Method::IsSynthetic() {
	return 0 != (accessFlags & AccessFlags::ACC_SYNTHETIC);
}

inline bool Method::IsAbstract() {
	return 0 != (accessFlags & AccessFlags::ACC_ABSTRACT);
}

inline bool Method::IsSynchronized() {
	return 0 != (accessFlags & AccessFlags::ACC_SYNCHRONIZED);
}

inline bool Method::IsBridge() {
	return 0 != (accessFlags & AccessFlags::ACC_BRIDGE);
}

inline bool Method::IsVarargs() {
	return 0 != (accessFlags & AccessFlags::ACC_VARARGS);
}

inline bool Method::IsNative() {
	return 0 != (accessFlags & AccessFlags::ACC_NATIVE);
}

inline bool Method::IsStrict() {
	return 0 != (accessFlags & AccessFlags::ACC_STRICT);
}

#endif //JVM_CLASS_HPP
