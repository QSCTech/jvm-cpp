/*
 * Created by 李晨曦 on 11/01/2018.
 */

#ifndef JVM_REFERENCES_HPP
#define JVM_REFERENCES_HPP
#include "Instruction.hpp"

class NEW;

class PUT_STATIC;

class GET_STATIC;

class PUT_FIELD;

class GET_FIELD;

class INSTANCE_OF;

class CHECK_CAST;

class LDC;

class LDC_W;

class LDC2_W;

void _ldc(Frame *frame, uint32_t index);

class INVOKE_SPECIAL;

class INVOKE_VIRTUAL;

class NEW: public Index16Instruction {
  public:
	void Execute(Frame *frame) override;
};

class PUT_STATIC: public Index16Instruction {
  public:
	void Execute(Frame *frame) override;
};

class GET_STATIC: public Index16Instruction {
  public:
	void Execute(Frame *frame) override;
};

class PUT_FIELD: public Index16Instruction {
  public:
	void Execute(Frame *frame) override;
};

class GET_FIELD: public Index16Instruction {
  public:
	void Execute(Frame *frame) override;
};

class INSTANCE_OF: public Index16Instruction {
  public:
	void Execute(Frame *frame) override;
};

class CHECK_CAST: public Index16Instruction {
  public:
	void Execute(Frame *frame) override;
};

class LDC: public Index8Instruction {
  public:
	void Execute(Frame *frame) override;
};

class LDC_W: public Index16Instruction {
  public:
	void Execute(Frame *frame) override;
};

class LDC2_W: public Index16Instruction {
  public:
	void Execute(Frame *frame) override;
};

class INVOKE_SPECIAL: public Index16Instruction {
  public:
	void Execute(Frame *frame) override;
};

class INVOKE_VIRTUAL: public Index16Instruction {
  public:
	void Execute(Frame *frame) override;
};

inline void INVOKE_VIRTUAL::Execute(Frame *frame) {
	auto rtcp = frame->method->belongClass->getConstantPool();
	auto methodRef = boost::any_cast<MethodRef *>(rtcp->getConstant(Index));
	auto descriptor = methodRef->description;
	if (methodRef->name == "println") {
		auto stack = frame->getOperandStack();
		if (descriptor == "(Z)V") {
			std::cout << (stack->PopInt() != 0) << std::endl;
		} else if (descriptor == "(C)V") {
			printf("%c\n", stack->PopInt());
		} else if (descriptor == "(B)V") {
			std::cout << stack->PopInt() << std::endl;
		} else if (descriptor == "(S)V") {
			std::cout << stack->PopInt() << std::endl;
		} else if (descriptor == "(I)V") {
			std::cout << stack->PopInt() << std::endl;
		} else if (descriptor == "(J)V") {
			std::cout << stack->PopLong() << std::endl;
		} else if (descriptor == "(F)V") {
			std::cout << stack->PopFloat() << std::endl;
		} else if (descriptor == "(D)V") {
			std::cout << stack->PopDouble() << std::endl;
		} else {
			throw TodoException(descriptor);
		}
		stack->PopRef();
	}
}

inline void INVOKE_SPECIAL::Execute(Frame *frame) {
	frame->getOperandStack()->PopRef();
	// TODO: complete it
}


inline void LDC::Execute(Frame *frame) {
	_ldc(frame, Index);
}

inline void LDC_W::Execute(Frame *frame) {
	_ldc(frame, Index);
}

inline void LDC2_W::Execute(Frame *frame) {
	auto stack = frame->getOperandStack();
	auto rtcp = frame->method->belongClass->getConstantPool();
	auto constant = rtcp->getConstant(Index);
	if (typeid(int64_t) == constant.type()) {
		stack->PushLong(boost::any_cast<int64_t>(constant));
	} else if (typeid(double) == constant.type()) {
		stack->PushDouble(boost::any_cast<double>(constant));
	} else {
		throw JavaClassFormatError("LDC2_W!");
	}
}


inline void NEW::Execute(Frame *frame) {
	auto cp = frame->method->belongClass->getConstantPool();
	for (auto content : cp->consts) {
		std::cout << content.type().name() << std::endl;
	}
	std::cout << boost::any_cast<MemberRef *>(cp->getConstant(Index))->name << std::endl;
	auto classRef = boost::any_cast<ClassRef *>(cp->getConstant(Index));
	auto newClass = classRef->ResolveClass();
	if (newClass->IsAbstract() || newClass->IsInterface()) {
		throw JavaInstantiationException();
	}
	auto ref = new Object(newClass);
	frame->getOperandStack()->PushRef(ref);
}

inline void PUT_STATIC::Execute(Frame *frame) {
	auto currentMethod = frame->method;
	auto currentClass = currentMethod->belongClass;
	auto rtcp = currentClass->getConstantPool();
	auto fieldRef = boost::any_cast<FieldRef *>(rtcp->getConstant(Index));
	auto field = fieldRef->ResolveField();
	auto owner = field->belongClass;
	if (!field->IsStatic()) {
		throw JavaIncompatibleClassChangeException();
	}
	if (field->IsFinal()) {
		if (currentClass != owner || currentMethod->name != "<clinit>") {
			throw JavaIllegalAccessException();
		}
	}
	auto descriptor = field->descriptor;
	auto slotId = field->slotId;
	auto slots = owner->getStaticVars();
	auto stack = frame->getOperandStack();
	auto head = descriptor[0];
	if (std::find(IntTypesByte.begin(), IntTypesByte.end(), head) != IntTypesByte.end()) {
		slots->SetInt(slotId, stack->PopInt());
	} else if (head == 'J') {
		slots->SetLong(slotId, stack->PopLong());
	} else if (head == 'F') {
		slots->SetFloat(slotId, stack->PopFloat());
	} else if (head == 'D') {
		slots->SetDouble(slotId, stack->PopDouble());
	} else if (head == 'L' || head == '[') {
		slots->SetRef(slotId, stack->PopRef());
	}
	
}

inline void GET_STATIC::Execute(Frame *frame) {
	auto rtcp = frame->method->belongClass->getConstantPool();
	auto fieldRef = boost::any_cast<FieldRef *>(rtcp->getConstant(Index));
	auto field = fieldRef->ResolveField();
	auto owner = field->belongClass;
	if (!field->IsStatic()) {
		throw JavaIncompatibleClassChangeException();
	}
	auto descriptor = field->descriptor;
	auto slotId = field->slotId;
	auto slots = owner->getStaticVars();
	auto stack = frame->getOperandStack();
	auto head = descriptor[0];
	if (std::find(IntTypesByte.begin(), IntTypesByte.end(), head) != IntTypesByte.end()) {
		stack->PushInt(slots->GetInt(slotId));
	} else if (head == 'J') {
		stack->PushLong(slots->GetLong(slotId));
	} else if (head == 'F') {
		stack->PushFloat(slots->GetFloat(slotId));
	} else if (head == 'D') {
		stack->PushDouble(slots->GetDouble(slotId));
	} else if (head == 'L' || head == '[') {
		stack->PushRef(slots->GetRef(slotId));
	}
	
}

inline void PUT_FIELD::Execute(Frame *frame) {
	auto currentMethod = frame->method;
	auto currentClass = currentMethod->belongClass;
	auto rtcp = currentClass->getConstantPool();
	auto fieldRef = boost::any_cast<FieldRef *>(rtcp->getConstant(Index));
	auto field = fieldRef->ResolveField();
	auto owner = field->belongClass;
	if (field->IsStatic()) {
		throw JavaIncompatibleClassChangeException();
	}
	if (field->IsFinal()) {
		if (currentClass != owner || currentMethod->name != "<init>") {
			throw JavaIllegalAccessException();
		}
	}
	auto descriptor = field->descriptor;
	auto slotId = field->slotId;
	auto stack = frame->getOperandStack();
	auto head = descriptor[0];
	if (std::find(IntTypesByte.begin(), IntTypesByte.end(), head) != IntTypesByte.end()) {
		auto val = stack->PopInt();
		auto ref = stack->PopRef();
		if (ref == nullptr) {
			throw JavaNullPointerException();
		}
		ref->fields->SetInt(slotId, val);
	} else if (head == 'J') {
		auto val = stack->PopLong();
		auto ref = stack->PopRef();
		if (ref == nullptr) {
			throw JavaNullPointerException();
		}
		ref->fields->SetLong(slotId, val);
	} else if (head == 'F') {
		auto val = stack->PopFloat();
		auto ref = stack->PopRef();
		if (ref == nullptr) {
			throw JavaNullPointerException();
		}
		ref->fields->SetFloat(slotId, val);
	} else if (head == 'D') {
		auto val = stack->PopDouble();
		auto ref = stack->PopRef();
		if (ref == nullptr) {
			throw JavaNullPointerException();
		}
		ref->fields->SetDouble(slotId, val);
	} else if (head == 'L' || head == '[') {
		auto val = stack->PopRef();
		auto ref = stack->PopRef();
		if (ref == nullptr) {
			throw JavaNullPointerException();
		}
		ref->fields->SetRef(slotId, val);
	}
}

inline void GET_FIELD::Execute(Frame *frame) {
	auto rtcp = frame->method->belongClass->getConstantPool();
	auto fieldRef = boost::any_cast<FieldRef *>(rtcp->getConstant(Index));
	auto field = fieldRef->ResolveField();
	auto owner = field->belongClass;
	if (field->IsStatic()) {
		throw JavaIncompatibleClassChangeException();
	}
	auto stack = frame->getOperandStack();
	auto ref = stack->PopRef();
	if (ref == nullptr) {
		throw JavaNullPointerException();
	}
	auto descriptor = field->descriptor;
	auto slotId = field->slotId;
	auto slots = ref->fields;
	auto head = descriptor[0];
	if (std::find(IntTypesByte.begin(), IntTypesByte.end(), head) != IntTypesByte.end()) {
		stack->PushInt(slots->GetInt(slotId));
	} else if (head == 'J') {
		stack->PushLong(slots->GetLong(slotId));
	} else if (head == 'F') {
		stack->PushFloat(slots->GetFloat(slotId));
	} else if (head == 'D') {
		stack->PushDouble(slots->GetDouble(slotId));
	} else if (head == 'L' || head == '[') {
		stack->PushRef(slots->GetRef(slotId));
	}
}

inline void INSTANCE_OF::Execute(Frame *frame) {
	auto stack = frame->getOperandStack();
	auto ref = stack->PopRef();
	if (ref == nullptr) {
		stack->PushInt(0);
		return;
	}
	auto rtcp = frame->method->belongClass->getConstantPool();
	auto classRef = boost::any_cast<ClassRef *>(rtcp->getConstant(Index));
	auto targetClass = classRef->ResolveClass();
	if (ref->IsInstanceOf(targetClass)) {
		stack->PushInt(1);
	} else {
		stack->PushInt(0);
	}
}

inline void CHECK_CAST::Execute(Frame *frame) {
	auto stack = frame->getOperandStack();
	auto ref = stack->PopRef();
	stack->PushRef(ref);
	if (ref == nullptr) {
		return;
	}
	auto rtcp = frame->method->belongClass->getConstantPool();
	auto classRef = boost::any_cast<ClassRef *>(rtcp->getConstant(Index));
	auto targetClass = classRef->ResolveClass();
	if (!ref->IsInstanceOf(targetClass)) {
		throw JavaClassCastException();
	}
}

inline void _ldc(Frame *frame, uint32_t index) {
	auto stack = frame->getOperandStack();
	auto rtcp = frame->method->belongClass->getConstantPool();
	auto constant = rtcp->getConstant(index);
	for (auto content : rtcp->consts) {
		std::cout << "content type: " << content.type().name() << std::endl;
	}
	std::cout << "constant().type: " << constant.type().name() << std::endl;
	std::cout << "typeid(ClassRef *).name(): " << typeid(ClassRef*).name() << std::endl;
	if (typeid(int32_t).name() == constant.type().name()) {
		stack->PushInt(boost::any_cast<int32_t>(constant));
	} else if (typeid(float).name() == constant.type().name()) {
		stack->PushFloat(boost::any_cast<float>(constant));
	} else if (typeid(std::string).name() == constant.type().name()) {
	
	} else if (typeid(ClassRef *).name() == constant.type().name()) {
	
	} else {
		throw TodoException("LDC!");
	}
}

#endif //JVM_REFERENCES_HPP

