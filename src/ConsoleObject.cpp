/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */


#include "ConsoleObject.h"
 
#include <iostream>

using namespace bit;
using namespace v8;
using namespace std;


Local<Object> ConsoleObject::getObject()
{
	HandleScope handleScope;
	
	// Get empty object to start with
	
	Local<Object> obj = getEmptyObject();
	
	// Add functions
	
	Local<FunctionTemplate> printTemplate = FunctionTemplate::New(print);
	Local<Function> printFunction = printTemplate->GetFunction();
	obj->Set(String::New("print"), printFunction);
	
	Local<FunctionTemplate> inputTemplate = FunctionTemplate::New(input);
	Local<Function> inputFunction = inputTemplate->GetFunction();
	obj->Set(String::New("input"), inputFunction);
	
	return handleScope.Close(obj);
}


Handle<Value> ConsoleObject::print(const Arguments &args)
{
	string message = ScriptObject::extractString(args, 0);
	
	// Print the string with a newline at the end
	
	cout << message << endl;
	
	return Undefined();
}


Handle<Value> ConsoleObject::input(const Arguments &args)
{
	HandleScope handleScope;
	
	// Query the user for a line of console input
	
	string result;
	getline(cin, result);
	
	// Create the V8 string and return it
	
	Local<String> resultString = String::New(result.c_str());
	
	return handleScope.Close(resultString);
}
