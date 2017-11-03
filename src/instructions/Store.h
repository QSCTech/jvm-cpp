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

class ISTORE;

class ISTORE_0;

class ISTORE_1;

class ISTORE_2;

class ISTORE_3;

class FSTORE;

class FSTORE_0;

class FSTORE_1;

class FSTORE_2;

class FSTORE_3;

class DSTORE;

class DSTORE_0;

class DSTORE_1;

class DSTORE_2;

class DSTORE_3;

class ASTORE;

class ASTORE_0;

class ASTORE_1;

class ASTORE_2;

class ASTORE_3;


void _lstore(Frame *frame, uint32_t index);
void _istore(Frame *frame, uint32_t index);
void _fstore(Frame *frame, uint32_t index);
void _dstore(Frame *frame, uint32_t index);
void _astore(Frame *frame, uint32_t index);

inline void _lstore(Frame *frame, uint32_t index)
{
	frame->getLocalVars()->SetLong(index, frame->getOperandStack()->PopLong());
}

inline void _istore(Frame *frame, uint32_t index)
{
	frame->getLocalVars()->SetInt(index, frame->getOperandStack()->PopInt());
}

inline void _fstore(Frame *frame, uint32_t index)
{
	frame->getLocalVars()->SetFloat(index, frame->getOperandStack()->PopFloat());
}

inline void _dstore(Frame *frame, uint32_t index)
{
	frame->getLocalVars()->SetDouble(index, frame->getOperandStack()->PopDouble());
}

inline void _astore(Frame *frame, uint32_t index)
{
	frame->getLocalVars()->SetRef(index, frame->getOperandStack()->PopRef());
}

class LSTORE: public Index8Instruction
{
  public:
	void Execute(Frame *frame) override;
};

class LSTORE_0: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LSTORE_1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LSTORE_2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LSTORE_3: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ISTORE: public Index8Instruction
{
  public:
	void Execute(Frame *frame) override;
};

class ISTORE_0: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ISTORE_1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ISTORE_2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ISTORE_3: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FSTORE: public Index8Instruction
{
  public:
	void Execute(Frame *frame) override;
};

class FSTORE_0: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FSTORE_1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FSTORE_2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FSTORE_3: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DSTORE: public Index8Instruction
{
  public:
	void Execute(Frame *frame) override;
};

class DSTORE_0: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DSTORE_1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DSTORE_2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DSTORE_3: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ASTORE: public Index8Instruction
{
  public:
	void Execute(Frame *frame) override;
};

class ASTORE_0: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ASTORE_1: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ASTORE_2: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class ASTORE_3: public NoOperandsInstruction
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

inline void ISTORE::Execute(Frame *frame)
{
	_istore(frame, this->Index);
}

inline void ISTORE_0::Execute(Frame *frame)
{
	_istore(frame, 0);
}

inline void ISTORE_1::Execute(Frame *frame)
{
	_istore(frame, 1);
}

inline void ISTORE_2::Execute(Frame *frame)
{
	_istore(frame, 2);
}

inline void ISTORE_3::Execute(Frame *frame)
{
	_istore(frame, 3);
}

inline void FSTORE::Execute(Frame *frame)
{
	_fstore(frame, this->Index);
}

inline void FSTORE_0::Execute(Frame *frame)
{
	_fstore(frame, 0);
}

inline void FSTORE_1::Execute(Frame *frame)
{
	_fstore(frame, 1);
}

inline void FSTORE_2::Execute(Frame *frame)
{
	_fstore(frame, 2);
}

inline void FSTORE_3::Execute(Frame *frame)
{
	_fstore(frame, 3);
}

inline void DSTORE::Execute(Frame *frame)
{
	_dstore(frame, this->Index);
}

inline void DSTORE_0::Execute(Frame *frame)
{
	_dstore(frame, 0);
}

inline void DSTORE_1::Execute(Frame *frame)
{
	_dstore(frame, 1);
}

inline void DSTORE_2::Execute(Frame *frame)
{
	_dstore(frame, 2);
}

inline void DSTORE_3::Execute(Frame *frame)
{
	_dstore(frame, 3);
}

inline void ASTORE::Execute(Frame *frame)
{
	_astore(frame, this->Index);
}

inline void ASTORE_0::Execute(Frame *frame)
{
	_astore(frame, 0);
}

inline void ASTORE_1::Execute(Frame *frame)
{
	_astore(frame, 1);
}

inline void ASTORE_2::Execute(Frame *frame)
{
	_astore(frame, 2);
}

inline void ASTORE_3::Execute(Frame *frame)
{
	_astore(frame, 3);
}

#endif //JVM_STORE_H
