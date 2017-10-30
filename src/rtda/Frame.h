//
// Created by 李晨曦 on 30/10/2017.
//

#ifndef JVM_FRAME_H
#define JVM_FRAME_H
#include <cstdint>
#include "Slot.h"

class Frame;

class Frame
{
  public:
	Frame* lower;
	LocalVars *localVars;
	OperandStack *operandStack;
	Frame(uint32_t maxLocals, uint32_t maxStack);
};

#endif //JVM_FRAME_H
