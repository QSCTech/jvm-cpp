//
// Created by 李晨曦 on 01/11/2017.
//

#include "Control.hpp"
void TABLE_SWITCH::FetchOperands(BytecodeReader *reader)
{
	reader->SkipPadding();
	this->defaultOffset = reader->ReadInt32();
	this->low = reader->ReadInt32();
	this->high = reader->ReadInt32();
	auto jumpCount = this->high - this->low + 1;
	this->jumpOffsets = reader->ReadInt32s(jumpCount);
}

void LOOKUP_SWITCH::FetchOperands(BytecodeReader *reader)
{
	reader->SkipPadding();
	this->defaultOffset = reader->ReadInt32();
	this->npairs = reader->ReadInt32();
	this->matchOffsets = reader->ReadInt32s(this->npairs * 2); /* multi 2, one for key, another for value */
}

void LOOKUP_SWITCH::Execute(Frame *frame)
{
	auto key = frame->getOperandStack()->PopInt();
	for (int i = 0; i < this->npairs * 2; i += 2)
	{
		if(this->matchOffsets[i] == key)
		{
			auto offset = this->matchOffsets[i+1];
			Branch(frame, offset);
			return;
		}
	}
}
