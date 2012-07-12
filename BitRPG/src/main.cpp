/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Application.h"
#include "Exception.h"
#include "AssetManager.h"

#include <iostream>

using namespace std;
using namespace bit;


int main(int argc, const char *argv[])
{
	try
	{
		AssetManagerPtr assetManager(new AssetManager);
	}
	catch (Exception &e)
	{
		cout << "Error: " << e.what() << endl;
	}
	
	return 0;
}
