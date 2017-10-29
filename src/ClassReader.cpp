#include "ClassReader.h"

uint8_t ClassReader::readUint8()
{
	uint8_t value = data[0];
	data.erase(data.begin());
	return value;
}

uint16_t ClassReader::readUint16()
{
	
	auto value = (uint16_t) data[0];
	value = value << 8 | data[1];
	data.erase(data.begin(), data.begin() + 2);
	return value;
}

uint32_t ClassReader::readUint32()
{
	auto value = (uint32_t) data[0];
	for (int i = 1; i < 4; i++)
	{
		value = value << 8 | data[i];
	}
	data.erase(data.begin(), data.begin() + 4);
	return value;
}

uint64_t ClassReader::readUint64()
{
	uint64_t value = (uint64_t) data[0];
	for (int i = 1; i < 8; i++)
	{
		value = value << 8 | data[i];
	}
	data.erase(data.begin(), data.begin() + 8);
	return value;
}

std::vector<uint16_t> ClassReader::readUint16s()
{
	uint16_t n = readUint16();
	auto vec = std::vector<uint16_t>(n);
	for (int i = 0; i < n; i++)
	{
		vec[i] = readUint16();
	}
	return vec;
}

std::vector<byte> ClassReader::readBytes(uint32_t n)
{
	std::vector<byte> vec(data.begin(), data.begin() + n);
	data.erase(data.begin(), data.begin() + n);
	return vec;
}