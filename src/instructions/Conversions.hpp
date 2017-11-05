//
// Created by 李晨曦 on 01/11/2017.
//

#ifndef JVM_CONVERSIONS_H
#define JVM_CONVERSIONS_H
#include "Instruction.hpp"

class D2F;

class D2I;

class D2L;

class F2D;

class F2I;

class F2L;

class I2D;

class I2F;

class I2L;

class I2B; /* int to byte */

class I2C; /* int to char */

class I2S; /* int to short */

class L2I;

class L2F;

class L2D;


class D2F: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class D2I: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class D2L: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class F2D: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class F2I: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class F2L: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class I2D: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class I2F: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class I2L: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class I2B: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class I2C: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class I2S: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class L2I: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class L2F: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class L2D: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};


inline void D2F::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto val = stack->PopDouble();
	stack->PushFloat((float) val);
}

inline void D2I::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto val = stack->PopDouble();
	stack->PushInt((int32_t) val);
}

inline void D2L::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto val = stack->PopDouble();
	stack->PushLong((int64_t) val);
}

inline void F2D::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto val = stack->PopFloat();
	stack->PushDouble((double) val);
}

inline void F2I::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto val = stack->PopFloat();
	stack->PushInt((int32_t) val);
}

inline void F2L::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto val = stack->PopFloat();
	stack->PushLong((int64_t) val);
}

inline void I2D::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto val = stack->PopInt();
	stack->PushDouble((double) val);
}

inline void I2F::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto val = stack->PopInt();
	stack->PushFloat((float) val);
}

inline void I2L::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto val = stack->PopInt();
	stack->PushLong((int64_t) val);
}

inline void L2D::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto val = stack->PopLong();
	stack->PushDouble((double) val);
}

inline void L2F::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto val = stack->PopLong();
	stack->PushFloat((float) val);
}

inline void L2I::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto val = stack->PopLong();
	stack->PushInt((int32_t) val);
}

inline void I2B::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto
	i = stack->PopInt(),
	b = (int32_t)((uint8_t)i);
	stack->PushInt(b);
}

inline void I2C::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto
	i = stack->PopInt(),
	c = (int32_t)((uint16_t)i);
	stack->PushInt(c);
}

inline void I2S::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto
	i = stack->PopInt(),
	s = (int32_t)((int16_t)i);
	stack->PushInt(s);
}

#endif //JVM_CONVERSIONS_H
