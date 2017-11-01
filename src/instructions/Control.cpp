//
// Created by 李晨曦 on 01/11/2017.
//

#include "Control.h"

void GOTO::Execute(Frame *frame)
{
	Branch(frame, this->Offset);
}

void TABLE_SWITCH::FetchOperands(BytecodeReader *reader)
{
	reader->SkipPadding();
	this->defaultOffset = reader->ReadInt32();
	this->low = reader->ReadInt32();
	this->high = reader->ReadInt32();
	auto jumpCount = this->high - this->low + 1;
	this->jumpOffsets = reader->ReadInt32s(jumpCount);
}