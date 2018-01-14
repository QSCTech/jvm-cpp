#ifndef JVM_SLOT_H
#define JVM_SLOT_H
#include <cstdint>
#include <vector>
#include "Class.hpp"

class OperandStack;

class OperandStack {
  public:
	uint32_t size;
	std::vector<Slot *> slots;
	explicit OperandStack(uint32_t maxStack);
	void PushInt(int32_t val);
	int32_t PopInt();
	void PushFloat(float val);
	float PopFloat();
	void PushLong(int64_t val);
	int64_t PopLong();
	void PushDouble(double val);
	double PopDouble();
	void PushRef(Object *ref);
	Object *PopRef();
	void PushSlot(Slot *slot);
	Slot *PopSlot();
};


inline void OperandStack::PushInt(int32_t val) {
	this->slots[this->size] = new Slot{val};
	this->size++;
}

inline int32_t OperandStack::PopInt() {
	this->size--;
	return this->slots[this->size]->num;
}

inline void OperandStack::PushFloat(float val) {
	this->slots[this->size] = new Slot{*(int32_t *) &val};
	this->size++;
}

inline float OperandStack::PopFloat() {
	this->size--;
	auto temp = this->slots[this->size]->num;
	return *(float *) &temp;
}

inline void OperandStack::PushLong(int64_t val) {
	this->slots[this->size]->num = (int32_t) val;
	this->slots[this->size + 1]->num = (int32_t) (val >> 32);
	this->size += 2;
}

inline int64_t OperandStack::PopLong() {
	this->size -= 2;
	auto low = (int64_t) this->slots[this->size]->num;
	auto high = (int64_t) this->slots[this->size + 1]->num;
	return high << 32 | low;
}

inline void OperandStack::PushDouble(double val) {
	DoubleUnion DU = {val};
	this->PushInt(DU.storage[0]);
	this->PushInt(DU.storage[1]);
}

inline double OperandStack::PopDouble() {
	DoubleUnion DU = {};
	DU.storage[1] = this->PopInt();
	DU.storage[0] = this->PopInt();
	return DU.value;
}

inline void OperandStack::PushRef(Object *ref) {
	this->slots[this->size]->ref = ref;
	this->size++;
}

inline Object *OperandStack::PopRef() {
	this->size--;
	auto ref = this->slots[size]->ref;
	this->slots[size]->ref = nullptr;
	return ref;
}

inline void OperandStack::PushSlot(Slot *slot) {
//	delete this->slots[this->size];
	this->slots[this->size] = slot;
	this->size++;
}

inline Slot *OperandStack::PopSlot() {
	this->size--;
	return this->slots[this->size];
}

#endif //JVM_SLOT_H
