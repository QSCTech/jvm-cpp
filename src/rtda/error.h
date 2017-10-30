//
// Created by 李晨曦 on 30/10/2017.
//

#ifndef JVM_ERROR_H
#define JVM_ERROR_H
#include <exception>
#include <string>

class JavaStackOverflowError;

class JavaStackOverflowError: std::exception
{
	std::string errString;
  public:
	JavaStackOverflowError() : 	errString("java.lang.JavaStackOverflowError!")
	{}
	const char *what() const throw() override
	{
		return this->errString.c_str();
	}
};

class JavaStackEmptyError: std::exception
{
	std::string errString;
  public:
	JavaStackEmptyError() : 	errString("java.lang.JavaStackEmptyError!")
	{}
	const char *what() const throw() override
	{
		return this->errString.c_str();
	}
};


#endif //JVM_ERROR_H
