//
// Created by 李晨曦 on 01/11/2017.
//

#include "Instruction.h"

std::vector<int32_t> BytecodeReader::ReadInt32s(int32_t size)
{
	std::vector<int32_t> vec(size);
	for (int i = 0; i < size; i++)
	{
		vec[i] = ReadInt32();
	}
	return vec;
}