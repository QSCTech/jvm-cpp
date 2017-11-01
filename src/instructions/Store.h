//
// Created by 李晨曦 on 01/11/2017.
//

#ifndef JVM_STORE_H
#define JVM_STORE_H
#include "Instruction.h"

class LSTORE;

class LSTORE_0;

class LSTORE_1;

class LSTORE_2;

class LSTORE_3;

void _lstore(Frame *frame, uint32_t index);

inline void _lstore(Frame *frame, uint32_t index)
{
	frame->getLocalVars()->SetLong(index, frame->getOperandStack()->PopLong());
}

class LSTORE: Index8Instruction
{
  public:
	void Execute(Frame *frame) override;
};

class LSTORE_0: NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LSTORE_1: NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LSTORE_2: NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LSTORE_3: NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

inline void LSTORE::Execute(Frame *frame)
{
	_lstore(frame, this->Index);
}

inline void LSTORE_0::Execute(Frame *frame)
{
	_lstore(frame, 0);
}

inline void LSTORE_1::Execute(Frame *frame)
{
	_lstore(frame, 1);
}

inline void LSTORE_2::Execute(Frame *frame)
{
	_lstore(frame, 2);
}

inline void LSTORE_3::Execute(Frame *frame)
{
	_lstore(frame, 3);
}
#endif //JVM_STORE_H
