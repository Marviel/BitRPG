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
#include "ScriptException.h"
#include "ItemObject.h"
#include "JSONValue.h"

#include <iostream>
#include <string>

using namespace bit;
using namespace std;


int main(int argc, const char *argv[])
{
	AssetManagerPtr assetManager(new AssetManager());
	ScriptManagerPtr scriptManager(new ScriptManager());
	
	try
	{
		JSONValue value = scriptManager->parseJSON("{\"a\": 6, \"names\": [\"Bernie\", \"William\"]}");
		cout << scriptManager->toJSON(value, true) << endl;
	}
	catch (Exception &e)
	{
		cout << e.what() << endl;
	}
	
	/*ConsoleObject console;
	scriptManager->registerObject(&console, "console");
	
	scriptManager->registerClass(ItemObject::constructor, "Item");
	*/
	
	/*
	try
	{
		scriptManager->runScript(assetManager->loadText("script.js"));
	}
	catch (bit::Exception &e)
	{
		cout << "bit::Exception: " << e.what() << endl;
	}
	*/
	
	
	/*
	while (true)
	{
		string statement;
		
		cout << "> ";
		getline(cin, statement);
		
		try
		{
			scriptManager->evaluate(statement);
		}
		catch (Exception &e)
		{
			cout << "bit::Exception: " << e.what() << endl;
		}
		catch (ScriptException &e)
		{
			cout << "bit::ScriptException" << endl;
		}
	}
	*/
	
	
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
