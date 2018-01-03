//
// Created by 李晨曦 on 11/12/2017.
//

#include "AccessFlags.hpp"

uint16_t AccessFlags::ACC_PUBLIC = 0x0001;
uint16_t AccessFlags::ACC_PRIVATE = 0x0002;
uint16_t AccessFlags::ACC_PROTECTED = 0x0004;
uint16_t AccessFlags::ACC_STATIC = 0x0008;
uint16_t AccessFlags::ACC_FINAL = 0x0010;
uint16_t AccessFlags::ACC_SUPER = 0x0020;
uint16_t AccessFlags::ACC_SYNCHRONIZED = 0x0020;
uint16_t AccessFlags::ACC_VOLATILE = 0x0040;
uint16_t AccessFlags::ACC_BRIDGE = 0x0040;
uint16_t AccessFlags::ACC_TRANSIENT = 0x0080;
uint16_t AccessFlags::ACC_VARARGS = 0x0080;
uint16_t AccessFlags::ACC_NATIVE = 0x0100;
uint16_t AccessFlags::ACC_INTERFACE = 0x0200;
uint16_t AccessFlags::ACC_ABSTRACT = 0x0400;
uint16_t AccessFlags::ACC_STRICT = 0x0800;
uint16_t AccessFlags::ACC_SYNTHETIC = 0x1000;
uint16_t AccessFlags::ACC_ANNOTATION = 0x2000;
uint16_t AccessFlags::ACC_ENUM = 0x4000;