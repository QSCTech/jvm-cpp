//
// Created by 李晨曦 on 30/10/2017.
//

#ifndef JVM_THREAD_H
#define JVM_THREAD_H
#include "Stack.h"
#include "Frame.h"

class Thread;

class Thread
{
	int pc;
	Stack *stack;
  public:
	explicit Thread(int frameMax);
	int getPc();
	void setPc(int pc);
	void PushFrame(Frame *frame);
	Frame *PopFrame();
	Frame *CurrentFrame();
};


inline int Thread::getPc()
{
	return this->pc;
}

inline void Thread::setPc(int pc)
{
	this->pc = pc;
}

inline void Thread::PushFrame(Frame *frame)
{
	this->stack->push(frame);
}

inline Frame *Thread::PopFrame()
{
	return this->stack->pop();
}

inline Frame *Thread::CurrentFrame()
{
	return this->stack->top();
}

#endif //JVM_THREAD_H
