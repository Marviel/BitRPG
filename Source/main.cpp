/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#include "Launcher.h"
#include "Entity.h"
#include "Exception.h"

#include <iostream>


int main(int argc, const char *argv[])
{
	try
	{
		Launcher launcher;
		launcher.run();
	}
	catch (bit::Exception &e)
	{
		std::cout << e.what() << "\n";
	}
	
	return 0;
}
