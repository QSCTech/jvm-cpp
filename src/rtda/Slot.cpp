//
// Created by 李晨曦 on 30/10/2017.
//

#include "Slot.hpp"

Slot::Slot(int32_t num) : num(num)
{}

Slot::Slot(Object* ref) : ref(ref)
{}

LocalVars::LocalVars(uint32_t maxLocals)
{
	this->slots = std::vector<Slot *>(maxLocals);
	for (uint32_t i = 0; i < maxLocals; i++)
	{
		this->slots[i] = new Slot(0);
	}
}

OperandStack::OperandStack(uint32_t maxStack) : size(0)
{
	this->slots = std::vector<Slot *>(maxStack);
	for (uint32_t i = 0; i < maxStack; i++)
	{
		this->slots[i] = new Slot(0);
	}
}