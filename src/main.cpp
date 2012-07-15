/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

//#include "Application.h"
#include "Exception.h"

#include "BitRPG.h"
#include "AssetManager.h"
#include "ScriptManager.h"
#include "ConsoleObject.h"
#include "ScriptTemplate.h"

#include <iostream>

using namespace bit;
using namespace std;


int main(int argc, const char *argv[])
{
	AssetManagerPtr assetManager(new AssetManager());
	ScriptManagerPtr scriptManager(new ScriptManager());
	
	try
	{
		ConsoleObject console;
		scriptManager->registerObject(&console, "console");
		
		scriptManager->runScript(assetManager->loadText("script.js"));
	}
	catch (bit::Exception &e)
	{
		cout << e.what() << endl;
	}
	
	
	/*
	try
	{
		ApplicationPtr app(new Application());
		app->start();
	}
	catch (Exception &e)
	{
		cout << "Error: " << e.what() << endl;
		return EXIT_FAILURE;
	}
	*/
	
	return EXIT_SUCCESS;
}
