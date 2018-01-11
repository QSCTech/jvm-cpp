//
// Created by 李晨曦 on 30/10/2017.
//

#include "Slot.hpp"
OperandStack::OperandStack(uint32_t maxStack) : size(0)
{
	this->slots = std::vector<Slot *>(maxStack);
	for (uint32_t i = 0; i < maxStack; i++)
	{
		this->slots[i] = new Slot(0);
	}
}