//
// Created by 李晨曦 on 30/10/2017.
//

#include "Thread.hpp"

Thread::Thread(int frameMax) : stack(new Stack(frameMax)), pc(0)
{}

Stack::Stack(uint32_t maxSize) : maxSize(maxSize), size(0), _top(nullptr)
{}

Frame::Frame(Thread* thread, uint32_t maxLocals, uint32_t maxStack) :thread(thread), lower(nullptr), nextPc(0)
{
	this->localVars = new LocalVars(maxLocals);
	this->operandStack = new OperandStack(maxStack);
}