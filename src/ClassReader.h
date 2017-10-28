#ifndef JVM_CLASSREADER_H
#define JVM_CLASSREADER_H
#include "util.h"

class ClassReader
{
	std::vector<BYTE> data;
	uint8_t readUint8();
	uint16_t readUint16();
	uint32_t readUint32();
	uint64_t readUint64();
	std::vector<uint16_t> readUint16s();
	std::vector<BYTE> readBytes(uint32_t n);
  public:
	ClassReader(std::vector<BYTE> data): data(data){}
};

#endif
