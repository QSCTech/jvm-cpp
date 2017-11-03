//
// Created by 李晨曦 on 01/11/2017.
//

#include "Extended.h"
#include "Loads.h"
#include "Store.h"
#include "Mathe.h"

void WIDE::FetchOperands(BytecodeReader *reader)
{
	auto opcode = reader->ReadUint8();
	switch (opcode)
	{
		case 0x15:
		{
			auto inst = new ILOAD();
			inst->Index = (uint32_t) reader->ReadUint16();
			this->modifiedInstruction = inst;
		}
		case 0x16:
		{
			auto inst = new LLOAD();
			inst->Index = (uint32_t) reader->ReadUint16();
			this->modifiedInstruction = inst;
		}
		case 0x17:
		{
			auto inst = new FLOAD();
			inst->Index = (uint32_t) reader->ReadUint16();
			this->modifiedInstruction = inst;
		}
		case 0x18:
		{
			auto inst = new DLOAD();
			inst->Index = (uint32_t) reader->ReadUint16();
			this->modifiedInstruction = inst;
		}
		case 0x19:
		{
			auto inst = new ALOAD();
			inst->Index = (uint32_t) reader->ReadUint16();
			this->modifiedInstruction = inst;
		}
		case 0x36:
		{
			auto inst = new ISTORE();
			inst->Index = (uint32_t) reader->ReadUint16();
			this->modifiedInstruction = inst;
		}
		case 0x37:
		{
			auto inst = new LSTORE();
			inst->Index = (uint32_t) reader->ReadUint16();
			this->modifiedInstruction = inst;
		}
		case 0x38:
		{
			auto inst = new FSTORE();
			inst->Index = (uint32_t) reader->ReadUint16();
			this->modifiedInstruction = inst;
		}
		case 0x39:
		{
			auto inst = new DSTORE();
			inst->Index = (uint32_t) reader->ReadUint16();
			this->modifiedInstruction = inst;
		}
		case 0x3a:
		{
			auto inst = new ALOAD();
			inst->Index = (uint32_t) reader->ReadUint16();
			this->modifiedInstruction = inst;
		}
		case 0x84:
		{
			auto inst = new IINC();
			inst->Index = (uint32_t) reader->ReadUint16();
			inst->Const = (int32_t) reader->ReadUint16();
			this->modifiedInstruction = inst;
		}
		case 0xa9:
		{
			throw JavaInstructionException("Unsupported opcode: 0xa9!");
		}
	}
	
}