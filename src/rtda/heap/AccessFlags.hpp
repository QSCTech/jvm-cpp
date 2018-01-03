//
// Created by 李晨曦 on 11/12/2017.
//

#ifndef JVM_ACCESSFLAGS_HPP
#define JVM_ACCESSFLAGS_HPP
#include <cstdint>
namespace AccessFlags
{
	extern uint16_t ACC_PUBLIC;            // class field method
	extern uint16_t ACC_PRIVATE;           //       field method
	extern uint16_t ACC_PROTECTED;         //       field method
	extern uint16_t ACC_STATIC;            //       field method
	extern uint16_t ACC_FINAL;             // class field method
	extern uint16_t ACC_SUPER;             // class
	extern uint16_t ACC_SYNCHRONIZED;      //             method
	extern uint16_t ACC_VOLATILE;          //       field
	extern uint16_t ACC_BRIDGE;            //             method
	extern uint16_t ACC_TRANSIENT;         //       field
	extern uint16_t ACC_VARARGS;           //             method
	extern uint16_t ACC_NATIVE;            //             method
	extern uint16_t ACC_INTERFACE;         // class
	extern uint16_t ACC_ABSTRACT;          // class       method
	extern uint16_t ACC_STRICT;            //             method
	extern uint16_t ACC_SYNTHETIC;         // class field method
	extern uint16_t ACC_ANNOTATION;        // class
	extern uint16_t ACC_ENUM;              // class field
};

#endif //JVM_ACCESSFLAGS_HPP
