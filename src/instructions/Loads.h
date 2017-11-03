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

class LLOAD;

class LLOAD_0;

class LLOAD_1;

class LLOAD_2;

class LLOAD_3;

class FLOAD;

class FLOAD_0;

class FLOAD_1;

class FLOAD_2;

class FLOAD_3;

class DLOAD;

class DLOAD_0;

class DLOAD_1;

class DLOAD_2;

class DLOAD_3;

class ALOAD;

class ALOAD_0;

class ALOAD_1;

class ALOAD_2;

class ALOAD_3;

void _iload(Frame *frame, uint32_t index);
void _lload(Frame *frame, uint32_t index);
void _fload(Frame *frame, uint32_t index);
void _dload(Frame *frame, uint32_t index);
void _aload(Frame *frame, uint32_t index);

inline void _iload(Frame *frame, uint32_t index)
{
	frame->getOperandStack()->PushInt(frame->getLocalVars()->GetInt(index));
}

inline void _lload(Frame *frame, uint32_t index)
{
	frame->getOperandStack()->PushLong(frame->getLocalVars()->GetLong(index));
}

inline void _fload(Frame *frame, uint32_t index)
{
	frame->getOperandStack()->PushFloat(frame->getLocalVars()->GetFloat(index));
}

inline void _dload(Frame *frame, uint32_t index)
{
	frame->getOperandStack()->PushDouble(frame->getLocalVars()->GetDouble(index));
}

inline void _aload(Frame *frame, uint32_t index)
{
	frame->getOperandStack()->PushRef(frame->getLocalVars()->GetRef(index));
}

class ILOAD: public Index8Instruction
{
  public:
	void Execute(Frame *frame) override;
};

class ILOAD_0: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ILOAD_1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ILOAD_2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ILOAD_3: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LLOAD: public Index8Instruction
{
  public:
	void Execute(Frame *frame) override;
};

class LLOAD_0: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LLOAD_1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LLOAD_2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LLOAD_3: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FLOAD: public Index8Instruction
{
  public:
	void Execute(Frame *frame) override;
};

class FLOAD_0: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FLOAD_1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FLOAD_2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FLOAD_3: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DLOAD: public Index8Instruction
{
  public:
	void Execute(Frame *frame) override;
};

class DLOAD_0: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DLOAD_1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DLOAD_2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DLOAD_3: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ALOAD: public Index8Instruction
{
  public:
	void Execute(Frame *frame) override;
};

class ALOAD_0: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ALOAD_1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ALOAD_2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ALOAD_3: public NoOperandsInstruction
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

inline void LLOAD::Execute(Frame *frame)
{
	_lload(frame, this->Index);
}

inline void LLOAD_0::Execute(Frame *frame)
{
	_lload(frame, 0);
}

inline void LLOAD_1::Execute(Frame *frame)
{
	_lload(frame, 1);
}

inline void LLOAD_2::Execute(Frame *frame)
{
	_lload(frame, 2);
}

inline void LLOAD_3::Execute(Frame *frame)
{
	_lload(frame, 3);
}

inline void FLOAD::Execute(Frame *frame)
{
	_fload(frame, this->Index);
}

inline void FLOAD_0::Execute(Frame *frame)
{
	_fload(frame, 0);
}

inline void FLOAD_1::Execute(Frame *frame)
{
	_fload(frame, 1);
}

inline void FLOAD_2::Execute(Frame *frame)
{
	_fload(frame, 2);
}

inline void FLOAD_3::Execute(Frame *frame)
{
	_fload(frame, 3);
}

inline void DLOAD::Execute(Frame *frame)
{
	_dload(frame, this->Index);
}

inline void DLOAD_0::Execute(Frame *frame)
{
	_dload(frame, 0);
}

inline void DLOAD_1::Execute(Frame *frame)
{
	_dload(frame, 1);
}

inline void DLOAD_2::Execute(Frame *frame)
{
	_dload(frame, 2);
}

inline void DLOAD_3::Execute(Frame *frame)
{
	_dload(frame, 3);
}

inline void ALOAD::Execute(Frame *frame)
{
	_aload(frame, this->Index);
}

inline void ALOAD_0::Execute(Frame *frame)
{
	_aload(frame, 0);
}

inline void ALOAD_1::Execute(Frame *frame)
{
	_aload(frame, 1);
}

inline void ALOAD_2::Execute(Frame *frame)
{
	_aload(frame, 2);
}

inline void ALOAD_3::Execute(Frame *frame)
{
	_aload(frame, 3);
}
#endif //JVM_LOADS_H
