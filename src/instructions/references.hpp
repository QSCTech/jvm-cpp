/*
 * Created by 李晨曦 on 11/01/2018.
 */

#ifndef JVM_REFERENCES_HPP
#define JVM_REFERENCES_HPP
#include "Instruction.hpp"

class NEW;

class NEW : public Index16Instruction{
  public:
	void Execute(Frame *frame) override;
};

inline void NEW::Execute(Frame *frame) {
	auto cp = frame->method->belongClass->getConstantPool();
	auto classRef = boost::any_cast<ClassRef*>(cp->getConstant(Index));
	auto newClass = classRef->ResolveClass();
	if (newClass->IsAbstract() || newClass->IsInterface()) {
		throw JavaInstantiationException();
	}
	auto ref = new Object(newClass);
	frame->getOperandStack()->PushRef(ref);
}
#endif //JVM_REFERENCES_HPP
