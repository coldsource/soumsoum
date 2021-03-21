#include <Exception/Exception.h>

Exception::Exception(int code, const std::string &error)
{
	this->code = code;
	this->error = error;
}
