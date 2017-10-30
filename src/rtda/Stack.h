//
// Created by 李晨曦 on 30/10/2017.
//

#ifndef JVM_STACK_H
#define JVM_STACK_H
#include <cstdint>
#include "Frame.h"
#include "error.h"

class Stack
{
	uint32_t maxSize;
	uint32_t size;
	Frame* _top;
  public:
	explicit Stack(uint32_t maxSize);
	void push(Frame* frame);
	Frame* pop();
	Frame* top();
};

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
	if(this->_top == nullptr)
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
	if(this->_top == nullptr)
	{
		throw JavaStackEmptyError();
	}
	return this->_top;
}


#endif //JVM_STACK_H
