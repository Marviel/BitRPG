/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#ifndef BitRPG_Exception_h
#define BitRPG_Exception_h

#include <string>

namespace bit
{
	class Exception
	{
	public:
		Exception() throw();
		Exception(std::string message) throw();
		
		std::string what() const throw();
		
	private:
		std::string message;
	};
}

#endif
