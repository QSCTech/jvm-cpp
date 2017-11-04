//
// Created by 李晨曦 on 02/11/2017.
//

#ifndef JVM_FACTORY_H
#define JVM_FACTORY_H
#include "Instruction.h"
#include "Comparisons.h"
#include "Constants.h"
#include "Control.h"
#include "Conversions.h"
#include "Extended.h"
#include "Loads.h"
#include "Mathe.h"
#include "stack.h"
#include "Store.h"

namespace Factory
{
	extern NOP *nop;
	extern ACONST_NULL *aconst_null;
	extern ICONST_M1 *iconst_m1;
	extern ICONST_0 *iconst_0;
	extern ICONST_1 *iconst_1;
	extern ICONST_2 *iconst_2;
	extern ICONST_3 *iconst_3;
	extern ICONST_4 *iconst_4;
	extern ICONST_5 *iconst_5;
	extern LCONST_0 *lconst_0;
	extern LCONST_1 *lconst_1;
	extern FCONST_0 *fconst_0;
	extern FCONST_1 *fconst_1;
	extern FCONST_2 *fconst_2;
	extern DCONST_0 *dconst_0;
	extern DCONST_1 *dconst_1;
	extern BIPUSH *bipush;
	extern SIPUSH *sipush;
	extern ILOAD *iload;
	extern ILOAD_0 *iload_0;
	extern ILOAD_1 *iload_1;
	extern ILOAD_2 *iload_2;
	extern ILOAD_3 *iload_3;
	extern LLOAD *lload;
	extern LLOAD_0 *lload_0;
	extern LLOAD_1 *lload_1;
	extern LLOAD_2 *lload_2;
	extern LLOAD_3 *lload_3;
	extern FLOAD *fload;
	extern FLOAD_0 *fload_0;
	extern FLOAD_1 *fload_1;
	extern FLOAD_2 *fload_2;
	extern FLOAD_3 *fload_3;
	extern DLOAD *dload;
	extern DLOAD_0 *dload_0;
	extern DLOAD_1 *dload_1;
	extern DLOAD_2 *dload_2;
	extern DLOAD_3 *dload_3;
	extern ALOAD *aload;
	extern ALOAD_0 *aload_0;
	extern ALOAD_1 *aload_1;
	extern ALOAD_2 *aload_2;
	extern ALOAD_3 *aload_3;
//	extern IALOAD*aload     ;
//	extern LALOAD*aload     ;
//	extern FALOAD*aload     ;
//	extern DALOAD*aload     ;
//	extern AALOAD*aload     ;
//	extern BALOAD*aload     ;
//	extern CALOAD*aload     ;
//	extern SALOAD*aload     ;
	extern ISTORE *istore;
	extern ISTORE_0 *istore_0;
	extern ISTORE_1 *istore_1;
	extern ISTORE_2 *istore_2;
	extern ISTORE_3 *istore_3;
	extern LSTORE *lstore;
	extern LSTORE_0 *lstore_0;
	extern LSTORE_1 *lstore_1;
	extern LSTORE_2 *lstore_2;
	extern LSTORE_3 *lstore_3;
	extern FSTORE *fstore;
	extern FSTORE_0 *fstore_0;
	extern FSTORE_1 *fstore_1;
	extern FSTORE_2 *fstore_2;
	extern FSTORE_3 *fstore_3;
	extern DSTORE *dstore;
	extern DSTORE_0 *dstore_0;
	extern DSTORE_1 *dstore_1;
	extern DSTORE_2 *dstore_2;
	extern DSTORE_3 *dstore_3;
	extern ASTORE *astore;
	extern ASTORE_0 *astore_0;
	extern ASTORE_1 *astore_1;
	extern ASTORE_2 *astore_2;
	extern ASTORE_3 *astore_3;
//	extern IASTORE*astore ;
//	extern LASTORE*astore ;
//	extern FASTORE*astore ;
//	extern DASTORE*astore ;
//	extern AASTORE*astore ;
//	extern BASTORE*astore ;
//	extern CASTORE*astore ;
//	extern SASTORE*astore ;
	extern POP *pop;
	extern POP2 *pop2;
	extern DUP *dup;
	extern DUP_X1 *dup_x1;
	extern DUP_X2 *dup_x2;
	extern DUP2 *dup2;
	extern DUP2_X1 *dup2_x1;
	extern DUP2_X2 *dup2_x2;
	extern SWAP *swap;
	extern IADD *iadd;
	extern LADD *ladd;
	extern FADD *fadd;
	extern DADD *dadd;
	extern ISUB *isub;
	extern LSUB *lsub;
	extern FSUB *fsub;
	extern DSUB *dsub;
	extern IMUL *imul;
	extern LMUL *lmul;
	extern FMUL *fmul;
	extern DMUL *dmul;
	extern IDIV *idiv;
	extern LDIV *ldiv;
	extern FDIV *fdiv;
	extern DDIV *ddiv;
	extern IREM *irem;
	extern LREM *lrem;
	extern FREM *frem;
	extern DREM *drem;
	extern INEG *ineg;
	extern LNEG *lneg;
	extern FNEG *fneg;
	extern DNEG *dneg;
	extern ISHL *ishl;
	extern LSHL *lshl;
	extern ISHR *ishr;
	extern LSHR *lshr;
	extern IUSHR *iushr;
	extern LUSHR *lushr;
	extern IAND *iand;
	extern LAND *land;
	extern IOR *ior;
	extern LOR *lor;
	extern IXOR *ixor;
	extern LXOR *lxor;
	extern I2L *i2l;
	extern I2F *i2f;
	extern I2D *i2d;
	extern L2I *l2i;
	extern L2F *l2f;
	extern L2D *l2d;
	extern F2I *f2i;
	extern F2L *f2l;
	extern F2D *f2d;
	extern D2I *d2i;
	extern D2L *d2l;
	extern D2F *d2f;
	extern I2B *i2b;
	extern I2C *i2c;
	extern I2S *i2s;
	extern LCMP *lcmp;
	extern FCMPL *fcmpl;
	extern FCMPG *fcmpg;
	extern DCMPL *dcmpl;
	extern DCMPG *dcmpg;
	extern IINC *iinc;
	extern IFEQ *ifeq;
	extern IFNE *ifne;
	extern IFGT *ifgt;
	extern IFGE *ifge;
	extern IFLT *iflt;
	extern IFLE *ifle;
	extern IF_ICMPEQ *if_icmpeq;
	extern IF_ICMPNE *if_icmpne;
	extern IF_ICMPLT *if_icmplt;
	extern IF_ICMPGE *if_icmpge;
	extern IF_ICMPGT *if_icmpgt;
	extern IF_ICMPLE *if_icmple;
	extern IF_ACMPEQ *if_acmpeq;
	extern IF_ACMPNE *if_acmpne;
	extern GOTO *_goto;
	extern TABLE_SWITCH *table_switch;
	extern LOOKUP_SWITCH *lookup_switch;
	extern WIDE *wide;
	extern IFNULL *ifnull;
	extern IFNONNULL *ifnonnull;
	extern GOTO_W *goto_w;
//	extern LRETURN*return;
//	extern FRETURN*return;
//	extern DRETURN*return;
//	extern ARETURN*return;
//	extern RETURN*return;
//	extern ARRAY_LENGTH*rraylength  ;
//	extern ATHROW*throw       ;
//	extern MONITOR_ENTER*onitorenter ;
//	extern MONITOR_EXIT*onitorexit  ;
//	extern INVOKE_NATIVE*nvoke_native;
	
	Instruction *NewInstruction(uint8_t opcode);
}
#endif //JVM_FACTORY_H
