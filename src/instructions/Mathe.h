//
// Created by 李晨曦 on 01/11/2017.
//

#ifndef JVM_MATHE_H
#define JVM_MATHE_H
#include "Instruction.h"
#include <cmath>

class DADD;

class FADD;

class IADD;

class LADD;

class DSUB;

class LSUB;

class FSUB;

class ISUB;

class DMUL;

class FMUL;

class IMUL;

class LMUL;

class DDIV;

class FDIV;

class IDIV;

class LDIV;

class DNEG;

class FNEG;

class INEG;

class LNEG;

class DREM;

class FREM;

class IREM;

class LREM;

class ISHL; // int 左位移

class ISHR; // int 算数右位移

class IUSHR; // int 逻辑右位移

class LSHL;

class LSHR;

class LUSHR;

class IAND;

class LAND;

class IINC;

class IREM: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LREM: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FREM: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DREM: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DADD: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FADD: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IADD: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LADD: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DSUB: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LSUB: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FSUB: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ISUB: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DMUL: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FMUL: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IMUL: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LMUL: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DDIV: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FDIV: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IDIV: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LDIV: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DNEG: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FNEG: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class INEG: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LNEG: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ISHL: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ISHR: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IUSHR: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LSHL: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LSHR: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LUSHR: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IAND: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LAND: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IINC: public Instruction
{
	uint32_t Index;
	int32_t Const;
  public:
	void FetchOperands(BytecodeReader *reader) override;
	void Execute(Frame *frame) override;
};
#endif //JVM_MATHE_H


inline void IREM::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	if (v2 == 0)
	{
		throw JavaArithmeticException("/ by zero");
	}
	stack->PushInt(v1 % v2);
}

inline void LREM::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopLong();
	auto v1 = stack->PopLong();
	if (v2 == 0)
	{
		throw JavaArithmeticException("/ by zero");
	}
	stack->PushLong(v1 % v2);
}

inline void FREM::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopFloat();
	auto v1 = stack->PopFloat();
	stack->PushFloat(fmod(v1, v2));
}

inline void DREM::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopDouble();
	auto v1 = stack->PopDouble();
	stack->PushDouble(fmod(v1, v2));
}


inline void DADD::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopDouble();
	auto v1 = stack->PopDouble();
	stack->PushDouble(v1 + v2);
}

inline void FADD::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopFloat();
	auto v1 = stack->PopFloat();
	stack->PushFloat(v1 + v2);
}

inline void LADD::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopLong();
	auto v1 = stack->PopLong();
	stack->PushLong(v1 + v2);
}

inline void IADD::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	stack->PushInt(v1 + v2);
}

inline void DSUB::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopDouble();
	auto v1 = stack->PopDouble();
	stack->PushDouble(v1 - v2);
}

inline void FSUB::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopFloat();
	auto v1 = stack->PopFloat();
	stack->PushFloat(v1 - v2);
}

inline void LSUB::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopLong();
	auto v1 = stack->PopLong();
	stack->PushLong(v1 - v2);
}

inline void ISUB::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	stack->PushInt(v1 - v2);
}

inline void DMUL::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopDouble();
	auto v1 = stack->PopDouble();
	stack->PushDouble(v1 * v2);
}

inline void FMUL::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopFloat();
	auto v1 = stack->PopFloat();
	stack->PushFloat(v1 * v2);
}

inline void LMUL::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopLong();
	auto v1 = stack->PopLong();
	stack->PushLong(v1 * v2);
}

inline void IMUL::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	stack->PushInt(v1 * v2);
}

inline void IDIV::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	if (v2 == 0)
	{
		throw JavaArithmeticException("/ by zero");
	}
	stack->PushInt(v1 / v2);
}

inline void LDIV::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopLong();
	auto v1 = stack->PopLong();
	if (v2 == 0)
	{
		throw JavaArithmeticException("/ by zero");
	}
	stack->PushLong(v1 / v2);
}

inline void FDIV::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopFloat();
	auto v1 = stack->PopFloat();
	if (v2 == 0)
	{
		throw JavaArithmeticException("/ by zero");
	}
	stack->PushFloat(v1 / v2);
}

inline void DDIV::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopDouble();
	auto v1 = stack->PopDouble();
	if (v2 == 0)
	{
		throw JavaArithmeticException("/ by zero");
	}
	stack->PushDouble(v1 / v2);
}


inline void DNEG::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v = stack->PopDouble();
	stack->PushDouble(-v);
}

inline void FNEG::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v = stack->PopFloat();
	stack->PushFloat(-v);
}

inline void LNEG::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v = stack->PopLong();
	stack->PushLong(-v);
}

inline void INEG::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v = stack->PopInt();
	stack->PushInt(-v);
}

inline void ISHL::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	auto bits = (uint32_t)v2 & 0x1f;
	stack->PushInt(v1 << bits);
}


inline void ISHR::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	auto bits = (uint32_t)v2 & 0x1f;
	stack->PushInt(v1 >> bits);
}

inline void IUSHR::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	auto bits = (uint32_t)v2 & 0x1f;
	stack->PushInt((int32_t)((uint32_t)v1 >> bits));
}

inline void LSHL::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopLong();
	auto bits = (uint32_t)v2 & 0x3f;
	stack->PushLong(v1 << bits);
}


inline void LSHR::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopLong();
	auto bits = (uint32_t)v2 & 0x3f;
	stack->PushLong(v1 >> bits);
}

inline void LUSHR::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopLong();
	auto bits = (uint32_t)v2 & 0x3f;
	stack->PushLong((int64_t)((uint64_t)v1 >> bits));
}


inline void IAND::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	stack->PushInt(v1 & v2);
}

inline void LAND::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopLong();
	auto v1 = stack->PopLong();
	stack->PushLong(v1 & v2);
}

inline void IINC::FetchOperands(BytecodeReader *reader)
{
	this->Index = (uint)reader->ReadUint8();
	this->Const = (int32_t) reader->ReadInt8(); // Why ?
}

inline void IINC::Execute(Frame *frame)
{
	auto localVals = frame->getLocalVars();
	localVals->SetInt(this->Index, localVals->GetInt(this->Index) + this->Const);
}
