//
// Created by 李晨曦 on 01/11/2017.
//

#ifndef JVM_EXTENDED_H
#define JVM_EXTENDED_H
#include "Instruction.h"

/**
 * @brief Wider index long
 */
class WIDE;

class IFNULL;

class IFNONNULL;

/**
 * @brief Branch always (wide index)
 */
class GOTO_W;

class WIDE: public Instruction
{
	Instruction *modifiedInstruction;
  public:
	void FetchOperands(BytecodeReader *reader) override;
	void Execute(Frame *frame) override;
};

class IFNULL: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
	
};


class IFNONNULL: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
	
};

class GOTO_W: public Instruction
{
  public:
	int32_t offset;
	void FetchOperands(BytecodeReader *reader) override;
	void Execute(Frame *frame) override;
};

inline void GOTO_W::FetchOperands(BytecodeReader *reader)
{
	this->offset = reader->ReadInt32();
}

inline void GOTO_W::Execute(Frame *frame)
{
	Branch(frame, this->offset);
}

inline void IFNONNULL::Execute(Frame *frame)
{
	if (frame->getOperandStack()->PopRef() != nullptr)
	{
		Branch(frame, this->Offset);
	}
}

inline void IFNULL::Execute(Frame *frame)
{
	if (frame->getOperandStack()->PopRef() == nullptr)
	{
		Branch(frame, this->Offset);
	}
}

inline void WIDE::Execute(Frame *frame)
{
	this->modifiedInstruction->Execute(frame);
}

#endif //JVM_EXTENDED_H
