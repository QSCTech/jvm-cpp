//
// Created by 李晨曦 on 30/10/2017.
//

#ifndef JVM_ERROR_H
#define JVM_ERROR_H
#include <exception>
#include <string>

class JavaStackOverflowError;

class JavaStackEmptyError;

class FileNotFoundError;

class FileReadError;

class DirOpenError;

struct ReadResult;

class JavaSrcError;

class ConstantPoolIndexInvalid;

class JavaClassFormatError;

class JavaArithmeticException;

class JavaStackOverflowError: std::exception
{
	std::string errString;
  public:
	JavaStackOverflowError() : errString("java.lang.JavaStackOverflowError!")
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
	JavaStackEmptyError() : errString("java.lang.JavaStackEmptyError!")
	{}
	
	const char *what() const throw() override
	{
		return this->errString.c_str();
	}
};

class FileReadError: std::exception
{
	std::string errString;
  public:
	explicit FileReadError(std::string filename)
	{
		errString = "Read file error: " + filename;
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class DirOpenError: std::exception
{
	std::string errString;
  public:
	explicit DirOpenError(std::string filename)
	{
		errString = "Open dir error: " + filename;
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class FileNotFoundError: std::exception
{
	std::string errString;
  public:
	explicit FileNotFoundError(std::string filename)
	{
		errString = "Jar file not found: " + filename;
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class JavaSrcError: std::exception
{
	std::string errString;
  public:
	explicit JavaSrcError(std::string filename)
	{
		errString = filename + " , ./jre or JAVA_HOME not exist or open fail";
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class ConstantPoolIndexInvalid: std::exception
{
	std::string errString;
  public:
	explicit ConstantPoolIndexInvalid()
	{
		errString = "java.lang.ConstantPoolIndexInvalid";
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class JavaClassFormatError: std::exception
{
	std::string errString;
  public:
	explicit JavaClassFormatError(std::string which)
	{
		errString = "java.lang.ClassFormatError: " + which;
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class JavaArithmeticException: std::exception
{
	std::string errString;
  public:
	explicit JavaArithmeticException(std::string which)
	{
		errString = "java.lang.JavaArithmeticException: " + which;
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class JavaInstructionException: std::exception
{
	std::string errString;
  public:
	explicit JavaInstructionException(std::string which)
	{
		errString = "java.lang.JavaInstructionException: " + which;
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class JavaRuntimeException: std::exception
{
	std::string errString;
  public:
	explicit JavaRuntimeException(std::string which)
	{
		errString = "java.lang.JavaRuntimeException: " + which;
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class JavaClassNotFoundException: std::exception
{
	std::string errString;
  public:
	explicit JavaClassNotFoundException(std::string name)
	{
		errString = "java.lang.ClassNotFoundException: " + name;
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};


class JavaIllegalAccessException: std::exception
{
	std::string errString;
  public:
	explicit JavaIllegalAccessException()
	{
		errString = "java.lang.IllegalAccessException";
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class JavaFieldNotExistException: std::exception
{
	std::string errString;
  public:
	explicit JavaFieldNotExistException()
	{
		errString = "java.lang.FieldNotExistException";
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class JavaInstantiationException: std::exception
{
	std::string errString;
  public:
	explicit JavaInstantiationException()
	{
		errString = "java.lang.InstantiationException";
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class JavaIncompatibleClassChangeException: std::exception
{
	std::string errString;
  public:
	explicit JavaIncompatibleClassChangeException()
	{
		errString = "java.lang.IncompatibleClassChangeException";
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};

class JavaNullPointerException: std::exception
{
	std::string errString;
  public:
	explicit JavaNullPointerException()
	{
		errString = "java.lang.NullPointerException";
	}
	
	const char *what() const throw() override
	{ return errString.c_str(); }
};


#endif //JVM_ERROR_H
