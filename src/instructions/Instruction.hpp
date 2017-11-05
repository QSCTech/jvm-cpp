//
// Created by 李晨曦 on 01/11/2017.
//

#ifndef JVM_INSTRUCTION_H
#define JVM_INSTRUCTION_H
#include "Thread.hpp"
#include "util.hpp"
class BytecodeReader;

class Instruction;

class NoOperandsInstruction;

class NOP;

class BranchInstruction;

class Index8Instruction;

class Index16Instruction;

void Branch(Frame *frame, int offset);

class BytecodeReader
{
	std::vector<byte> code;
	int pc;
  public:
	int getPc() const;
  public:
	void Reset(const std::vector<byte> &code, int pc);
	uint8_t ReadUint8();
	int8_t ReadInt8();
	uint16_t ReadUint16();
	int16_t ReadInt16();
	int32_t ReadInt32();
	std::vector<int32_t> ReadInt32s(int32_t size);
	void SkipPadding();
};

class Instruction
{
  public:
	virtual void FetchOperands(BytecodeReader *reader) = 0;
	virtual void Execute(Frame* frame) = 0;
};

class NoOperandsInstruction: public Instruction
{
  public:
	void FetchOperands(BytecodeReader *reader) override;
};

class BranchInstruction: public Instruction
{
  public:
	int Offset;
	void FetchOperands(BytecodeReader *reader) override;
};

class Index8Instruction: public Instruction
{
  public:
	uint32_t Index;
	void FetchOperands(BytecodeReader *reader) override;
};

class Index16Instruction: public Instruction
{
  public:
	uint32_t Index;
	void FetchOperands(BytecodeReader *reader) override;
};


class NOP: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

/**
 * @brief skip padding to keep pc % 4 == 0, but why?
 */
inline void BytecodeReader::SkipPadding()
{
	while (this->pc % 4 != 0)
	{
		this->ReadUint8();
	}
}


inline void NoOperandsInstruction::FetchOperands(BytecodeReader *reader)
{}

inline void BranchInstruction::FetchOperands(BytecodeReader *reader)
{
	this->Offset = (int32_t)reader->ReadInt16();
}

inline void Index8Instruction::FetchOperands(BytecodeReader *reader)
{
	this->Index = (uint32_t)reader->ReadUint8();
}

inline void Index16Instruction::FetchOperands(BytecodeReader *reader)
{
	this->Index = (uint32_t)reader->ReadUint16();
}

inline void BytecodeReader::Reset(const std::vector<byte> &code, int pc)
{
	this->code = code;
	this->pc = pc;
}

inline uint8_t BytecodeReader::ReadUint8()
{
	printf("pc: %d\n", this->pc);
	auto i = this->code[this->pc];
	this->pc++;
	return i;
}

inline int8_t BytecodeReader::ReadInt8()
{
	return (int8_t) this->ReadUint8();
}

inline uint16_t BytecodeReader::ReadUint16()
{
	auto byte1 = (uint16_t)this->ReadUint8();
	auto byte2 = (uint16_t)this->ReadUint8();
	return (byte1 << 8) | byte2;
}

inline int16_t BytecodeReader::ReadInt16()
{
	return (int16_t)this->ReadUint16();
}

inline int32_t BytecodeReader::ReadInt32()
{
	auto byte1 = (int32_t)this->ReadUint8();
	auto byte2 = (int32_t)this->ReadUint8();
	auto byte3 = (int32_t)this->ReadUint8();
	auto byte4 = (int32_t)this->ReadUint8();
	return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

inline int BytecodeReader::getPc() const
{
	return pc;
}

inline void Branch(Frame *frame, int offset)
{
	frame->setNextPc(frame->getThread()->getPc() + offset);
}

#endif //JVM_INSTRUCTION_H
