//
// Created by 李晨曦 on 01/11/2017.
//

#ifndef JVM_CONSTANTS_H
#define JVM_CONSTANTS_H
#include "Instruction.h"
class ACONST_NULL;

class DCONST_0;

class DCONST_1;

class FCONST_0;

class FCONST_1;

class FCONST_2;

class ICONST_M1;

class ICONST_0;

class ICONST_1;

class ICONST_2;

class ICONST_3;

class ICONST_4;

class ICONST_5;

class LCONST_0;

class LCONST_1;

class BIPUSH;

class SIPUSH;

class ACONST_NULL: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DCONST_0: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DCONST_1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FCONST_0: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FCONST_1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FCONST_2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ICONST_M1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ICONST_0: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ICONST_1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ICONST_2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ICONST_3: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ICONST_4: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ICONST_5: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LCONST_0: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LCONST_1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class BIPUSH: public Instruction
{
	int8_t val;
  public:
	void FetchOperands(BytecodeReader *reader) override;
	void Execute(Frame *frame) override;
};

class SIPUSH: public Instruction
{
	int16_t val;
  public:
	void FetchOperands(BytecodeReader *reader) override;
	void Execute(Frame *frame) override;
};

inline void ACONST_NULL::Execute(Frame *frame)
{
	frame->getOperandStack()->PushRef(nullptr);
}

inline void DCONST_0::Execute(Frame *frame)
{
	frame->getOperandStack()->PushDouble(0.0);
}

inline void DCONST_1::Execute(Frame *frame)
{
	frame->getOperandStack()->PushDouble(1.0);
}

inline void FCONST_0::Execute(Frame *frame)
{
	frame->getOperandStack()->PushFloat(0.0);
}

inline void FCONST_1::Execute(Frame *frame)
{
	frame->getOperandStack()->PushFloat(1.0);
}

inline void FCONST_2::Execute(Frame *frame)
{
	frame->getOperandStack()->PushFloat(2.0);
}

inline void ICONST_M1::Execute(Frame *frame)
{
	frame->getOperandStack()->PushInt(-1);
}

inline void ICONST_0::Execute(Frame *frame)
{
	frame->getOperandStack()->PushInt(0);
}

inline void ICONST_1::Execute(Frame *frame)
{
	frame->getOperandStack()->PushInt(1);
}

inline void ICONST_2::Execute(Frame *frame)
{
	frame->getOperandStack()->PushInt(2);
}

inline void ICONST_3::Execute(Frame *frame)
{
	frame->getOperandStack()->PushInt(3);
}

inline void ICONST_4::Execute(Frame *frame)
{
	frame->getOperandStack()->PushInt(4);
}

inline void ICONST_5::Execute(Frame *frame)
{
	frame->getOperandStack()->PushInt(5);
}


inline void LCONST_0::Execute(Frame *frame)
{
	frame->getOperandStack()->PushLong(0);
}

inline void LCONST_1::Execute(Frame *frame)
{
	frame->getOperandStack()->PushLong(1);
}

inline void BIPUSH::FetchOperands(BytecodeReader *reader)
{
	this->val = reader->ReadInt8();
}

inline void BIPUSH::Execute(Frame *frame)
{
	auto i = (int32_t)this->val;
	frame->getOperandStack()->PushInt(i);
}

inline void SIPUSH::FetchOperands(BytecodeReader *reader)
{
	this->val = reader->ReadInt16();
}

inline void SIPUSH::Execute(Frame *frame)
{
	auto i = (int32_t)this->val;
	frame->getOperandStack()->PushInt(i);
}


#endif //JVM_CONSTANTS_H
