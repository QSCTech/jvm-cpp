//
// Created by 李晨曦 on 30/10/2017.
//

#include "Frame.h"

Frame::Frame(uint32_t maxLocals, uint32_t maxStack) : lower(nullptr)
{
	this->localVars = new LocalVars(maxLocals);
	this->operandStack = new OperandStack(maxStack);
}
