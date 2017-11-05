//
// Created by 李晨曦 on 01/11/2017.
//

#ifndef JVM_COMPARISONS_H
#define JVM_COMPARISONS_H
#include "Instruction.hpp"

class LCMP;

class FCMPG;

class FCMPL;

void _fcmp(Frame *frame, bool gFlag);

class DCMPG;

class DCMPL;

class IFEQ; /* == 0 */

class IFNE; /* != 0 */

class IFLT; /* < 0 */

class IFLE; /* <= 0 */

class IFGT; /* > 0 */

class IFGE; /* >= 0 */

class IF_ICMPEQ; /* == */

class IF_ICMPNE; /* != */

class IF_ICMPLT; /* < */

class IF_ICMPLE; /* <= */

class IF_ICMPGT; /* > */

class IF_ICMPGE; /* >= */

class IF_ACMPEQ;

class IF_ACMPNE;


void _dcmp(Frame *frame, bool gFlag);

class FCMPG: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class FCMPL: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class LCMP: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DCMPG: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class DCMPL: public NoOperandsInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IFEQ: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IFNE: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IFLT: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IFLE: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IFGT: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IFGE: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IF_ICMPEQ: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};


class IF_ICMPNE: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};


class IF_ICMPLT: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};


class IF_ICMPLE: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};


class IF_ICMPGT: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};


class IF_ICMPGE: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IF_ACMPEQ: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};

class IF_ACMPNE: public BranchInstruction
{
  public:
	void Execute(Frame *frame) override;
};

inline void _fcmp(Frame *frame, bool gFlag)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopFloat();
	auto v1 = stack->PopFloat();
	if (v1 > v2)
	{
		stack->PushInt(1);
	} else if (v1 == v2)
	{
		stack->PushInt(0);
	} else if (v1 < v2)
	{
		stack->PushInt(-1);
	} else if (gFlag)
	{
		stack->PushInt(1);
	} else
	{
		stack->PushInt(-1);
	}
}

inline void _dcmp(Frame *frame, bool gFlag)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopDouble();
	auto v1 = stack->PopDouble();
	if (v1 > v2)
	{
		stack->PushInt(1);
	} else if (v1 == v2)
	{
		stack->PushInt(0);
	} else if (v1 < v2)
	{
		stack->PushInt(-1);
	} else if (gFlag)
	{
		stack->PushInt(1);
	} else
	{
		stack->PushInt(-1);
	}
}

inline void LCMP::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopLong();
	auto v1 = stack->PopLong();
	if (v1 > v2)
	{
		stack->PushInt(1);
	} else if (v1 == v2)
	{
		stack->PushInt(0);
	} else
	{
		stack->PushInt(-1);
	}
}

inline void FCMPG::Execute(Frame *frame)
{
	_fcmp(frame, true);
}

inline void FCMPL::Execute(Frame *frame)
{
	_fcmp(frame, false);
}

inline void DCMPG::Execute(Frame *frame)
{
	_dcmp(frame, true);
}

inline void DCMPL::Execute(Frame *frame)
{
	_dcmp(frame, false);
}

inline void IFEQ::Execute(Frame *frame)
{
	if (frame->getOperandStack()->PopInt() == 0)
	{
		Branch(frame, this->Offset);
	}
}

inline void IFNE::Execute(Frame *frame)
{
	if (frame->getOperandStack()->PopInt() != 0)
	{
		Branch(frame, this->Offset);
	}
}

inline void IFGT::Execute(Frame *frame)
{
	if (frame->getOperandStack()->PopInt() > 0)
	{
		Branch(frame, this->Offset);
	}
}

inline void IFGE::Execute(Frame *frame)
{
	if (frame->getOperandStack()->PopInt() >= 0)
	{
		Branch(frame, this->Offset);
	}
}

inline void IFLT::Execute(Frame *frame)
{
	if (frame->getOperandStack()->PopInt() < 0)
	{
		Branch(frame, this->Offset);
	}
}

inline void IFLE::Execute(Frame *frame)
{
	if (frame->getOperandStack()->PopInt() <= 0)
	{
		Branch(frame, this->Offset);
	}
}


inline void IF_ICMPEQ::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	if (v1 == v2)
	{
		Branch(frame, this->Offset);
	}
}


inline void IF_ICMPNE::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	if (v1 != v2)
	{
		Branch(frame, this->Offset);
	}
}


inline void IF_ICMPGT::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	if (v1 > v2)
	{
		Branch(frame, this->Offset);
	}
}


inline void IF_ICMPGE::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	if (v1 >= v2)
	{
		Branch(frame, this->Offset);
	}
}


inline void IF_ICMPLT::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	if (v1 < v2)
	{
		Branch(frame, this->Offset);
	}
}


inline void IF_ICMPLE::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto v2 = stack->PopInt();
	auto v1 = stack->PopInt();
	if (v1 <= v2)
	{
		Branch(frame, this->Offset);
	}
}

inline void IF_ACMPEQ::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto r2 = stack->PopRef();
	auto r1 = stack->PopRef();
	if (r1 == r2)
	{
		Branch(frame, this->Offset);
	}
}

inline void IF_ACMPNE::Execute(Frame *frame)
{
	auto stack = frame->getOperandStack();
	auto r2 = stack->PopRef();
	auto r1 = stack->PopRef();
	if (r1 != r2)
	{
		Branch(frame, this->Offset);
	}
}

#endif //JVM_COMPARISONS_H
