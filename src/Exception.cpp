/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Exception.h"

#include <assert.h>

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
