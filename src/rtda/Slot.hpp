#ifndef JVM_SLOT_H
#define JVM_SLOT_H
#include <cstdint>
#include <vector>
#include "Object.hpp"
union Slot;

class LocalVars;

class OperandStack;

union DoubleUnion;

union DoubleUnion
{
	double value;
	int32_t storage[2];
};

class OperandStack
{
  public:
	uint32_t size;
	std::vector<Slot* > slots;
	explicit OperandStack(uint32_t maxStack);
	void PushInt(int32_t val);
	int32_t PopInt();
	void PushFloat(float val);
	float PopFloat();
	void PushLong(int64_t val);
	int64_t PopLong();
	void PushDouble (double val);
	double PopDouble();
	void PushRef(Object* ref);
	Object* PopRef();
	void PushSlot(Slot* slot);
	Slot* PopSlot();
};

class LocalVars
{
  public:
	std::vector<Slot* > slots;
	explicit LocalVars(uint32_t maxLocals);
	void SetInt(uint32_t index, int32_t val);
	int32_t GetInt(uint32_t index);
	void SetFloat(uint32_t index, float val);
	float GetFloat(uint32_t index);
	void SetLong(uint32_t index, int64_t val);
	int64_t GetLong(uint32_t index);
	void SetDouble(uint32_t index, double val);
	double GetDouble(uint32_t index);
	void SetRef(uint32_t index, Object* ref);
	Object* GetRef(uint32_t index);
};

union Slot
{
  public:
	int32_t num;
	Object* ref;
	explicit Slot(int32_t num);
	explicit Slot(Object *ref);
};

inline void LocalVars::SetInt(uint32_t index, int32_t val)
{
	this->slots[index]->num = val;
}

inline int32_t LocalVars::GetInt(uint32_t index)
{
	return this->slots[index]->num;
}

inline void LocalVars::SetFloat(uint32_t index, float val)
{
	this->slots[index]->num = *(int *) (&val);
}

inline float LocalVars::GetFloat(uint32_t index)
{
	return *(float *) &(this->slots[index]->num);
}

inline void LocalVars::SetLong(uint32_t index, int64_t val)
{
	this->slots[index]->num = (int32_t) val;
	this->slots[index + 1]->num = (int32_t) (val >> 32);
}

inline int64_t LocalVars::GetLong(uint32_t index)
{
	auto low = (int64_t) (this->slots[index]->num);
	auto high = (int64_t) (this->slots[index + 1]->num);
	return high << 32 | low;
}

inline void LocalVars::SetDouble(uint32_t index, double val)
{
	DoubleUnion DU = {val};
	this->SetInt(index, DU.storage[0]);
	this->SetInt(index + 1, DU.storage[1]);
}

inline double LocalVars::GetDouble(uint32_t index)
{
	DoubleUnion DU = {};
	DU.storage[0] = this->GetInt(index);
	DU.storage[1] = this->GetInt(index+1);
	return DU.value;
}

inline void LocalVars::SetRef(uint32_t index, Object *ref)
{
	this->slots[index]->ref = ref;
}

inline Object *LocalVars::GetRef(uint32_t index)
{
	return this->slots[index]->ref;
}

inline void OperandStack::PushInt(int32_t val)
{
	this->slots[this->size]->num = val;
	this->size++;
}

inline int32_t OperandStack::PopInt()
{
	this->size--;
	return this->slots[this->size]->num;
}

inline void OperandStack::PushFloat(float val)
{
	this->slots[this->size]->num = *(int32_t*)&val;
	this->size++;
}

inline float OperandStack::PopFloat()
{
	this->size--;
	auto temp = this->slots[this->size]->num;
	return *(float*)&temp;
}

inline void OperandStack::PushLong(int64_t val)
{
	this->slots[this->size]->num = (int32_t) val;
	this->slots[this->size + 1]->num = (int32_t) (val >> 32);
	this->size += 2;
}

inline int64_t OperandStack::PopLong()
{
	this->size -= 2;
	auto low = (int64_t) this->slots[this->size]->num;
	auto high = (int64_t) this->slots[this->size + 1]->num;
	return high << 32 | low;
}

inline void OperandStack::PushDouble(double val)
{
	DoubleUnion DU = {val};
	this->PushInt(DU.storage[0]);
	this->PushInt(DU.storage[1]);
}

inline double OperandStack::PopDouble()
{
	DoubleUnion DU = {};
	DU.storage[1] = this->PopInt();
	DU.storage[0] = this->PopInt();
	return DU.value;
}

inline void OperandStack::PushRef(Object *ref)
{
	this->slots[this->size]->ref = ref;
	this->size++;
}

inline Object *OperandStack::PopRef()
{
	this->size--;
	auto ref = this->slots[size]->ref;
	this->slots[size]->ref = nullptr;
	return ref;
}

inline void OperandStack::PushSlot(Slot *slot)
{
	delete this->slots[this->size];
	this->slots[this->size] = slot;
	this->size++;
}

inline Slot *OperandStack::PopSlot()
{
	this->size--;
	return this->slots[this->size];
}

#endif //JVM_SLOT_H
