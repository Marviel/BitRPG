/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Application.h"
#include "Exception.h"

#include <iostream>

using namespace bit;
using namespace std;


int main(int argc, const char *argv[])
{
	try
	{
		ApplicationPtr app(new Application());
		app->start();
	}
	catch (Exception &e)
	{
		cout << "Error: " << e.what() << endl;
	}
	
	return 0;
}
