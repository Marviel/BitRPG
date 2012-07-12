/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#include "Exception.h"

using namespace bit;
using std::string;


Exception::Exception() throw()
{
}


Exception::Exception(std::string message) throw()
{
	this->message = message;
}


string Exception::what() const throw()
{
	return message;
}
