#ifndef JVM_CLASSREADER_H
#define JVM_CLASSREADER_H
#include "util.hpp"

class ClassReader
{
	std::vector<byte> data;
  public:
	uint8_t readUint8();
	uint16_t readUint16();
	uint32_t readUint32();
	uint64_t readUint64();
	std::vector<uint16_t> readUint16s();
	std::vector<byte> readBytes(uint32_t n);
	
	ClassReader(std::vector<byte> data) : data(data)
	{}
};

#endif
