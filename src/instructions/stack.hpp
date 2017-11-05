//
// Created by 李晨曦 on 01/11/2017.
//

#ifndef JVM_STACK_H
#define JVM_STACK_H
#include "Instruction.hpp"

class POP;

class POP2;

/*
bottom -> top
[...][c][b][a]
             \_
               |
               V
[...][c][b][a][a]
*/
class DUP;

/*
bottom -> top
[...][c][b][a]
          __/
         |
         V
[...][c][a][b][a]
*/
class DUP_X1;

/*
bottom -> top
[...][c][b][a]
       _____/
      |
      V
[...][a][c][b][a]
*/
class DUP_X2;

/*
bottom -> top
[...][c][b][a]____
          \____   |
               |  |
               V  V
[...][c][b][a][b][a]
*/
class DUP2;

/*
bottom -> top
[...][c][b][a]
       _/ __/
      |  |
      V  V
[...][b][a][c][b][a]
*/
class DUP2_X1;

/*
bottom -> top
[...][d][c][b][a]
       ____/ __/
      |   __/
      V  V
[...][b][a][d][c][b][a]
*/

class DUP2_X2;

class SWAP;

class POP: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class POP2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DUP: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DUP_X1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DUP_X2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DUP2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DUP2_X1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DUP2_X2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class SWAP: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};


// pop 4 bytes
inline void POP::Execute(Frame *frame)
{
	frame->getOperandStack()->PopSlot();
}

// pop 8 bytes
inline void POP2::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	stack->PopSlot();
	stack->PopSlot();
}

inline void DUP::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto slot = stack->PopSlot();
	stack->PushSlot(slot);
	auto newSlot = new Slot(slot->ref);
	stack->PushSlot(newSlot);
}

inline void DUP_X1::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto slot1 = stack->PopSlot();
	auto slot2 = stack->PopSlot();
	auto newSlot = new Slot(slot1->ref);
	stack->PushSlot(newSlot);
	stack->PushSlot(slot2);
	stack->PushSlot(slot1);
}

inline void DUP_X2::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto slot1 = stack->PopSlot();
	auto slot2 = stack->PopSlot();
	auto slot3 = stack->PopSlot();
	auto newSlot = new Slot(slot1->ref);
	stack->PushSlot(newSlot);
	stack->PushSlot(slot3);
	stack->PushSlot(slot2);
	stack->PushSlot(slot1);
}

inline void DUP2::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto slot1 = stack->PopSlot();
	auto slot2 = stack->PopSlot();
	stack->PushSlot(slot2);
	stack->PushSlot(slot1);
	auto newSlot1 = new Slot(slot1->ref);
	auto newSlot2 = new Slot(slot2->ref);
	stack->PushSlot(newSlot2);
	stack->PushSlot(newSlot1);
}

inline void DUP2_X1::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto slot1 = stack->PopSlot();
	auto slot2 = stack->PopSlot();
	auto slot3 = stack->PopSlot();
	auto newSlot1 = new Slot(slot1->ref);
	auto newSlot2 = new Slot(slot2->ref);
	stack->PushSlot(newSlot2);
	stack->PushSlot(newSlot1);
	stack->PushSlot(slot3);
	stack->PushSlot(slot2);
	stack->PushSlot(slot1);
}

inline void DUP2_X2::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto slot1 = stack->PopSlot();
	auto slot2 = stack->PopSlot();
	auto slot3 = stack->PopSlot();
	auto slot4 = stack->PopSlot();
	auto newSlot1 = new Slot(slot1->ref);
	auto newSlot2 = new Slot(slot2->ref);
	stack->PushSlot(newSlot2);
	stack->PushSlot(newSlot1);
	stack->PushSlot(slot4);
	stack->PushSlot(slot3);
	stack->PushSlot(slot2);
	stack->PushSlot(slot1);
}

inline void SWAP::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto slot1 = stack->PopSlot();
	auto slot2 = stack->PopSlot();
	stack->PushSlot(slot1);
	stack->PushSlot(slot2);
}

#endif //JVM_STACK_H
