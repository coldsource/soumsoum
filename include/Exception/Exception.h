#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>

class Exception
{
protected:
	int code = 0;
	std::string error;
	
public:
	Exception(int code, const std::string &error);
	
	int GetCode() const { return code; }
	const std::string &GetError() const { return error; }
};

#endif
