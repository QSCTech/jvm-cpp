//
// Created by 李晨曦 on 01/11/2017.
//

#ifndef JVM_CONTROL_H
#define JVM_CONTROL_H
#include "Instruction.hpp"

class GOTO;

class TABLE_SWITCH;

class TABLE_SWITCH;

class LOOKUP_SWITCH;

class GOTO: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class TABLE_SWITCH: public Instruction
{
	int32_t defaultOffset;
	int32_t high;
	int32_t low;
	std::vector<int32_t> jumpOffsets;
  public:
	void FetchOperands(BytecodeReader *reader) override;
	void Execute(Frame *frame) override;
};

class LOOKUP_SWITCH: public Instruction
{
	int32_t defaultOffset;
	int32_t npairs;
	std::vector<int32_t> matchOffsets;
  public:
	void FetchOperands(BytecodeReader *reader) override;
	void Execute(Frame *frame) override;
};

inline void GOTO::Execute(Frame *frame)
{
	printf("GOTO.Offset: %d, frame.pc: %d\n", this->Offset, frame->getNextPc());
	Branch(frame, this->Offset);
}


inline void TABLE_SWITCH::Execute(Frame *frame)
{
	auto index = frame->getOperandStack()->PopInt();
	int32_t offset;
	if (index >= this->low && index <= this->high)
	{
		offset = int(this->jumpOffsets[index - this->low]);
	} else
	{
		offset = int(this->defaultOffset);
	}
	Branch(frame, offset);
}

#endif //JVM_CONTROL_H
