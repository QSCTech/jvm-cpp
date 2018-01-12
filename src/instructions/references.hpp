/*
 * Created by 李晨曦 on 11/01/2018.
 */

#ifndef JVM_REFERENCES_HPP
#define JVM_REFERENCES_HPP
#include "Instruction.hpp"

class NEW;

class PUSH_STATIC;

class GET_STATIC;

class NEW: public Index16Instruction {
  public:
	void Execute(Frame *frame) override;
};

class PUSH_STATIC: public Index16Instruction {
  public:
	void Execute(Frame *frame) override;
};

class GET_STATIC: public Index16Instruction {
  public:
	void Execute(Frame *frame) override;
};


inline void NEW::Execute(Frame *frame) {
	auto cp = frame->method->belongClass->getConstantPool();
	auto classRef = boost::any_cast<ClassRef *>(cp->getConstant(Index));
	auto newClass = classRef->ResolveClass();
	if (newClass->IsAbstract() || newClass->IsInterface()) {
		throw JavaInstantiationException();
	}
	auto ref = new Object(newClass);
	frame->getOperandStack()->PushRef(ref);
}

inline void PUSH_STATIC::Execute(Frame *frame) {
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

#endif //JVM_REFERENCES_HPP

