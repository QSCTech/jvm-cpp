//
// Created by 李晨曦 on 01/11/2017.
//

#ifndef JVM_LOADS_H
#define JVM_LOADS_H
#include "Instruction.h"

class ILOAD;

class ILOAD_0;

class ILOAD_1;

class ILOAD_2;

class ILOAD_3;

void _iload(Frame *frame, uint32_t index);

inline void _iload(Frame *frame, uint32_t index)
{
	frame->getOperandStack()->PushInt(frame->getLocalVars()->GetInt(index));
}

class ILOAD: Index8Instruction
{
  public:
	void Execute(Frame *frame) override;
};

class ILOAD_0: NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ILOAD_1: NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ILOAD_2: NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ILOAD_3: NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

inline void ILOAD::Execute(Frame *frame)
{
	_iload(frame, this->Index);
}

inline void ILOAD_0::Execute(Frame *frame)
{
	_iload(frame, 0);
}

inline void ILOAD_1::Execute(Frame *frame)
{
	_iload(frame, 1);
}

inline void ILOAD_2::Execute(Frame *frame)
{
	_iload(frame, 2);
}

inline void ILOAD_3::Execute(Frame *frame)
{
	_iload(frame, 3);
}

#endif //JVM_LOADS_H
