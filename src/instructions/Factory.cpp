//
// Created by 李晨曦 on 02/11/2017.
//

#include "Factory.hpp"

auto Factory::nop = new NOP();
auto Factory::aconst_null = new ACONST_NULL();
auto Factory::iconst_m1 = new ICONST_M1();
auto Factory::iconst_0 = new ICONST_0();
auto Factory::iconst_1 = new ICONST_1();
auto Factory::iconst_2 = new ICONST_2();
auto Factory::iconst_3 = new ICONST_3();
auto Factory::iconst_4 = new ICONST_4();
auto Factory::iconst_5 = new ICONST_5();
auto Factory::lconst_0 = new LCONST_0();
auto Factory::lconst_1 = new LCONST_1();
auto Factory::fconst_0 = new FCONST_0();
auto Factory::fconst_1 = new FCONST_1();
auto Factory::fconst_2 = new FCONST_2();
auto Factory::dconst_0 = new DCONST_0();
auto Factory::dconst_1 = new DCONST_1();
auto Factory::bipush = new BIPUSH();
auto Factory::sipush = new SIPUSH();
auto Factory::iload = new ILOAD();
auto Factory::iload_0 = new ILOAD_0();
auto Factory::iload_1 = new ILOAD_1();
auto Factory::iload_2 = new ILOAD_2();
auto Factory::iload_3 = new ILOAD_3();
auto Factory::lload = new LLOAD();
auto Factory::lload_0 = new LLOAD_0();
auto Factory::lload_1 = new LLOAD_1();
auto Factory::lload_2 = new LLOAD_2();
auto Factory::lload_3 = new LLOAD_3();
auto Factory::fload = new FLOAD();
auto Factory::fload_0 = new FLOAD_0();
auto Factory::fload_1 = new FLOAD_1();
auto Factory::fload_2 = new FLOAD_2();
auto Factory::fload_3 = new FLOAD_3();
auto Factory::dload = new DLOAD();
auto Factory::dload_0 = new DLOAD_0();
auto Factory::dload_1 = new DLOAD_1();
auto Factory::dload_2 = new DLOAD_2();
auto Factory::dload_3 = new DLOAD_3();
auto Factory::aload = new ALOAD();
auto Factory::aload_0 = new ALOAD_0();
auto Factory::aload_1 = new ALOAD_1();
auto Factory::aload_2 = new ALOAD_2();
auto Factory::aload_3 = new ALOAD_3();
// iaload      = new IALOAD();
// laload      = new LALOAD();
// faload      = new FALOAD();
// daload      = new DALOAD();
// aaload      = new AALOAD();
// baload      = new BALOAD();
// caload      = new CALOAD();
// saload      = new SALOAD();
auto Factory::istore = new ISTORE();
auto Factory::istore_0 = new ISTORE_0();
auto Factory::istore_1 = new ISTORE_1();
auto Factory::istore_2 = new ISTORE_2();
auto Factory::istore_3 = new ISTORE_3();
auto Factory::lstore = new LSTORE();
auto Factory::lstore_0 = new LSTORE_0();
auto Factory::lstore_1 = new LSTORE_1();
auto Factory::lstore_2 = new LSTORE_2();
auto Factory::lstore_3 = new LSTORE_3();
auto Factory::fstore = new FSTORE();
auto Factory::fstore_0 = new FSTORE_0();
auto Factory::fstore_1 = new FSTORE_1();
auto Factory::fstore_2 = new FSTORE_2();
auto Factory::fstore_3 = new FSTORE_3();
auto Factory::dstore = new DSTORE();
auto Factory::dstore_0 = new DSTORE_0();
auto Factory::dstore_1 = new DSTORE_1();
auto Factory::dstore_2 = new DSTORE_2();
auto Factory::dstore_3 = new DSTORE_3();
auto Factory::astore = new ASTORE();
auto Factory::astore_0 = new ASTORE_0();
auto Factory::astore_1 = new ASTORE_1();
auto Factory::astore_2 = new ASTORE_2();
auto Factory::astore_3 = new ASTORE_3();
// iastore  = new IASTORE();
// lastore  = new LASTORE();
// fastore  = new FASTORE();
// dastore  = new DASTORE();
// aastore  = new AASTORE();
// bastore  = new BASTORE();
// castore  = new CASTORE();
// sastore  = new SASTORE();
auto Factory::pop = new POP();
auto Factory::pop2 = new POP2();
auto Factory::dup = new DUP();
auto Factory::dup_x1 = new DUP_X1();
auto Factory::dup_x2 = new DUP_X2();
auto Factory::dup2 = new DUP2();
auto Factory::dup2_x1 = new DUP2_X1();
auto Factory::dup2_x2 = new DUP2_X2();
auto Factory::swap = new SWAP();
auto Factory::iadd = new IADD();
auto Factory::ladd = new LADD();
auto Factory::fadd = new FADD();
auto Factory::dadd = new DADD();
auto Factory::isub = new ISUB();
auto Factory::lsub = new LSUB();
auto Factory::fsub = new FSUB();
auto Factory::dsub = new DSUB();
auto Factory::imul = new IMUL();
auto Factory::lmul = new LMUL();
auto Factory::fmul = new FMUL();
auto Factory::dmul = new DMUL();
auto Factory::idiv = new IDIV();
auto Factory::ldiv = new LDIV();
auto Factory::fdiv = new FDIV();
auto Factory::ddiv = new DDIV();
auto Factory::irem = new IREM();
auto Factory::lrem = new LREM();
auto Factory::frem = new FREM();
auto Factory::drem = new DREM();
auto Factory::ineg = new INEG();
auto Factory::lneg = new LNEG();
auto Factory::fneg = new FNEG();
auto Factory::dneg = new DNEG();
auto Factory::ishl = new ISHL();
auto Factory::lshl = new LSHL();
auto Factory::ishr = new ISHR();
auto Factory::lshr = new LSHR();
auto Factory::iushr = new IUSHR();
auto Factory::lushr = new LUSHR();
auto Factory::iand = new IAND();
auto Factory::land = new LAND();
auto Factory::ior = new IOR();
auto Factory::lor = new LOR();
auto Factory::ixor = new IXOR();
auto Factory::lxor = new LXOR();
auto Factory::i2l = new I2L();
auto Factory::i2f = new I2F();
auto Factory::i2d = new I2D();
auto Factory::l2i = new L2I();
auto Factory::l2f = new L2F();
auto Factory::l2d = new L2D();
auto Factory::f2i = new F2I();
auto Factory::f2l = new F2L();
auto Factory::f2d = new F2D();
auto Factory::d2i = new D2I();
auto Factory::d2l = new D2L();
auto Factory::d2f = new D2F();
auto Factory::i2b = new I2B();
auto Factory::i2c = new I2C();
auto Factory::i2s = new I2S();
auto Factory::lcmp = new LCMP();
auto Factory::fcmpl = new FCMPL();
auto Factory::fcmpg = new FCMPG();
auto Factory::dcmpl = new DCMPL();
auto Factory::dcmpg = new DCMPG();
auto Factory::iinc = new IINC();
auto Factory::ifeq = new IFEQ();
auto Factory::ifne = new IFNE();
auto Factory::ifgt = new IFGT();
auto Factory::ifge = new IFGE();
auto Factory::iflt = new IFLT();
auto Factory::ifle = new IFLE();
auto Factory::if_icmpeq = new IF_ICMPEQ();
auto Factory::if_icmpne = new IF_ICMPNE();
auto Factory::if_icmplt = new IF_ICMPLT();
auto Factory::if_icmpge = new IF_ICMPGE();
auto Factory::if_icmpgt = new IF_ICMPGT();
auto Factory::if_icmple = new IF_ICMPLE();
auto Factory::if_acmpeq = new IF_ACMPEQ();
auto Factory::if_acmpne = new IF_ACMPNE();
auto Factory::_goto = new GOTO();
auto Factory::table_switch = new TABLE_SWITCH();
auto Factory::lookup_switch = new LOOKUP_SWITCH();
auto Factory::wide = new WIDE();
auto Factory::ifnull = new IFNULL();
auto Factory::ifnonnull = new IFNONNULL();
auto Factory::goto_w = new GOTO_W();
//	lreturn = new LRETURN();
// freturn = new FRETURN();
// dreturn = new DRETURN();
// areturn = new ARETURN();
// _return = new RETURN();
// arraylength   = new ARRAY_LENGTH();
// athrow        = new ATHROW();
// monitorenter  = new MONITOR_ENTER();
// monitorexit   = new MONITOR_EXIT();
// invoke_native = new INVOKE_NATIVE();

Instruction *Factory::NewInstruction(uint8_t opcode) {
	switch (opcode) {
		case 0x00:
			return nop;
		case 0x01:
			return aconst_null;
		case 0x02:
			return iconst_m1;
		case 0x03:
			return iconst_0;
		case 0x04:
			return iconst_1;
		case 0x05:
			return iconst_2;
		case 0x06:
			return iconst_3;
		case 0x07:
			return iconst_4;
		case 0x08:
			return iconst_5;
		case 0x09:
			return lconst_0;
		case 0x0a:
			return lconst_1;
		case 0x0b:
			return fconst_0;
		case 0x0c:
			return fconst_1;
		case 0x0d:
			return fconst_2;
		case 0x0e:
			return dconst_0;
		case 0x0f:
			return dconst_1;
		case 0x10:
			return bipush;
		case 0x11:
			return sipush;
		case 0x12:
			return new LDC();
		case 0x13:
			return new LDC_W();
		case 0x14:
			return new LDC2_W();
		case 0x15:
			return iload;
		case 0x16:
			return lload;
		case 0x17:
			return fload;
		case 0x18:
			return dload;
		case 0x19:
			return aload;
		case 0x1a:
			return iload_0;
		case 0x1b:
			return iload_1;
		case 0x1c:
			return iload_2;
		case 0x1d:
			return iload_3;
		case 0x1e:
			return lload_0;
		case 0x1f:
			return lload_1;
		case 0x20:
			return lload_2;
		case 0x21:
			return lload_3;
		case 0x22:
			return fload_0;
		case 0x23:
			return fload_1;
		case 0x24:
			return fload_2;
		case 0x25:
			return fload_3;
		case 0x26:
			return dload_0;
		case 0x27:
			return dload_1;
		case 0x28:
			return dload_2;
		case 0x29:
			return dload_3;
		case 0x2a:
			return aload_0;
		case 0x2b:
			return aload_1;
		case 0x2c:
			return aload_2;
		case 0x2d:
			return aload_3;
			// case 0x2e:
			// 	return iaload;
			// case 0x2f:
			// 	return laload;
			// case 0x30:
			// 	return faload;
			// case 0x31:
			// 	return daload;
			// case 0x32:
			// 	return aaload;
			// case 0x33:
			// 	return baload;
			// case 0x34:
			// 	return caload;
			// case 0x35:
			// 	return saload;
		case 0x36:
			return istore;
		case 0x37:
			return lstore;
		case 0x38:
			return fstore;
		case 0x39:
			return dstore;
		case 0x3a:
			return astore;
		case 0x3b:
			return istore_0;
		case 0x3c:
			return istore_1;
		case 0x3d:
			return istore_2;
		case 0x3e:
			return istore_3;
		case 0x3f:
			return lstore_0;
		case 0x40:
			return lstore_1;
		case 0x41:
			return lstore_2;
		case 0x42:
			return lstore_3;
		case 0x43:
			return fstore_0;
		case 0x44:
			return fstore_1;
		case 0x45:
			return fstore_2;
		case 0x46:
			return fstore_3;
		case 0x47:
			return dstore_0;
		case 0x48:
			return dstore_1;
		case 0x49:
			return dstore_2;
		case 0x4a:
			return dstore_3;
		case 0x4b:
			return astore_0;
		case 0x4c:
			return astore_1;
		case 0x4d:
			return astore_2;
		case 0x4e:
			return astore_3;
			// case 0x4f:
			// 	return iastore;
			// case 0x50:
			// 	return lastore;
			// case 0x51:
			// 	return fastore;
			// case 0x52:
			// 	return dastore;
			// case 0x53:
			// 	return aastore;
			// case 0x54:
			// 	return bastore;
			// case 0x55:
			// 	return castore;
			// case 0x56:
			// 	return sastore;
		case 0x57:
			return pop;
		case 0x58:
			return pop2;
		case 0x59:
			return dup;
		case 0x5a:
			return dup_x1;
		case 0x5b:
			return dup_x2;
		case 0x5c:
			return dup2;
		case 0x5d:
			return dup2_x1;
		case 0x5e:
			return dup2_x2;
		case 0x5f:
			return swap;
		case 0x60:
			return iadd;
		case 0x61:
			return ladd;
		case 0x62:
			return fadd;
		case 0x63:
			return dadd;
		case 0x64:
			return isub;
		case 0x65:
			return lsub;
		case 0x66:
			return fsub;
		case 0x67:
			return dsub;
		case 0x68:
			return imul;
		case 0x69:
			return lmul;
		case 0x6a:
			return fmul;
		case 0x6b:
			return dmul;
		case 0x6c:
			return idiv;
		case 0x6d:
			return ldiv;
		case 0x6e:
			return fdiv;
		case 0x6f:
			return ddiv;
		case 0x70:
			return irem;
		case 0x71:
			return lrem;
		case 0x72:
			return frem;
		case 0x73:
			return drem;
		case 0x74:
			return ineg;
		case 0x75:
			return lneg;
		case 0x76:
			return fneg;
		case 0x77:
			return dneg;
		case 0x78:
			return ishl;
		case 0x79:
			return lshl;
		case 0x7a:
			return ishr;
		case 0x7b:
			return lshr;
		case 0x7c:
			return iushr;
		case 0x7d:
			return lushr;
		case 0x7e:
			return iand;
		case 0x7f:
			return land;
		case 0x80:
			return ior;
		case 0x81:
			return lor;
		case 0x82:
			return ixor;
		case 0x83:
			return lxor;
		case 0x84:
			return iinc;
		case 0x85:
			return i2l;
		case 0x86:
			return i2f;
		case 0x87:
			return i2d;
		case 0x88:
			return l2i;
		case 0x89:
			return l2f;
		case 0x8a:
			return l2d;
		case 0x8b:
			return f2i;
		case 0x8c:
			return f2l;
		case 0x8d:
			return f2d;
		case 0x8e:
			return d2i;
		case 0x8f:
			return d2l;
		case 0x90:
			return d2f;
		case 0x91:
			return i2b;
		case 0x92:
			return i2c;
		case 0x93:
			return i2s;
		case 0x94:
			return lcmp;
		case 0x95:
			return fcmpl;
		case 0x96:
			return fcmpg;
		case 0x97:
			return dcmpl;
		case 0x98:
			return dcmpg;
		case 0x99:
			return ifeq;
		case 0x9a:
			return ifne;
		case 0x9b:
			return iflt;
		case 0x9c:
			return ifge;
		case 0x9d:
			return ifgt;
		case 0x9e:
			return ifle;
		case 0x9f:
			return if_icmpeq;
		case 0xa0:
			return if_icmpne;
		case 0xa1:
			return if_icmplt;
		case 0xa2:
			return if_icmpge;
		case 0xa3:
			return if_icmpgt;
		case 0xa4:
			return if_icmple;
		case 0xa5:
			return if_acmpeq;
		case 0xa6:
			return if_acmpne;
		case 0xa7:
			return _goto;
			// case 0xa8:
			// 	return &JSR{};
			// case 0xa9:
			// 	return &RET{};
		case 0xaa:
			return table_switch;
		case 0xab:
			return lookup_switch;
			// case 0xac:
			// 	return ireturn;
			// case 0xad:
			// 	return lreturn;
			// case 0xae:
			// 	return freturn;
			// case 0xaf:
			// 	return dreturn;
			// case 0xb0:
			// 	return areturn;
			// case 0xb1:
			// 	return _return;
		case 0xb2:
			return new GET_STATIC();
		case 0xb3:
			return new PUT_STATIC();
		case 0xb4:
			return new GET_FIELD();
		case 0xb5:
			return new PUT_FIELD();
		case 0xb6:
			return new INVOKE_VIRTUAL();
		case 0xb7:
			return new INVOKE_SPECIAL();
			// case 0xb8:
			// 	return &INVOKE_STATIC{};
			// case 0xb9:
			// 	return &INVOKE_INTERFACE{};
			// case 0xba:
			// 	return &INVOKE_DYNAMIC{};
		case 0xbb:
			return new NEW();
			// case 0xbc:
			// 	return &NEW_ARRAY{};
			// case 0xbd:
			// 	return &ANEW_ARRAY{};
			// case 0xbe:
			// 	return arraylength;
			// case 0xbf:
			// 	return athrow;
		case 0xc0:
			return new CHECK_CAST();
		case 0xc1:
			return new INSTANCE_OF();
			// case 0xc2:
			// 	return monitorenter;
			// case 0xc3:
			// 	return monitorexit;
		case 0xc4:
			return wide;
			// case 0xc5:
			// 	return &MULTI_ANEW_ARRAY{};
		case 0xc6:
			return ifnull;
		case 0xc7:
			return ifnonnull;
		case 0xc8:
			return goto_w;
			// case 0xc9:
			// 	return &JSR_W{};
			// case 0xca: breakpoint
			// case 0xfe: impdep1
			// case 0xff: impdep2
		default:
			throw JavaRuntimeException("Unsupported opcode: " + std::to_string(opcode));
	}
	
}