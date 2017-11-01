//
// Created by 李晨曦 on 30/10/2017.
//

#ifndef JVM_THREAD_H
#define JVM_THREAD_H
#include "error.h"
#include "Slot.h"

class Thread;

class Stack;

class Frame;

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

class Stack
{
	uint32_t maxSize;
	uint32_t size;
	Frame *_top;
  public:
	explicit Stack(uint32_t maxSize);
	void push(Frame *frame);
	Frame *pop();
	Frame *top();
};


class Frame
{
	OperandStack *operandStack;
	LocalVars *localVars;
	Thread *thread;
	int nextPc;
  public:
	Frame(Thread *thread, uint32_t maxLocals, uint32_t maxStack);
	Frame *lower;
	LocalVars *getLocalVars() const;
	OperandStack *getOperandStack() const;
	Thread *getThread() const;
	int getNextPc() const;
	void setNextPc(int nextPc);
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

inline void Stack::push(Frame *frame)
{
	if (this->size >= this->maxSize)
	{
		throw JavaStackOverflowError();
	}
	if (this->_top != nullptr)
	{
		frame->lower = this->_top;
	}
	this->_top = frame;
	this->size++;
}

inline Frame *Stack::pop()
{
	if (this->_top == nullptr)
	{
		throw JavaStackEmptyError();
	}
	auto top = this->_top;
	this->_top = top->lower;
	top->lower = nullptr;
	this->size--;
	return top;
}

inline Frame *Stack::top()
{
	if (this->_top == nullptr)
	{
		throw JavaStackEmptyError();
	}
	return this->_top;
}

inline OperandStack *Frame::getOperandStack() const
{
	return operandStack;
}

inline LocalVars *Frame::getLocalVars() const
{
	return localVars;
}

inline Thread *Frame::getThread() const
{
	return thread;
}


inline int Frame::getNextPc() const
{
	return nextPc;
}

inline void Frame::setNextPc(int nextPc)
{
	this->nextPc = nextPc;
}

#endif //JVM_THREAD_H
