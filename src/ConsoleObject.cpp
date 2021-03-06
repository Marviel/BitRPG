/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "ConsoleObject.h"
#include "ScriptException.h"
 
#include <iostream>

using namespace bit;
using namespace v8;
using namespace std;


Local<Object> ConsoleObject::createInstance()
{
	HandleScope handleScope;
	
	// Create the function template
	
	Local<FunctionTemplate> functionTemplate = FunctionTemplate::New();
	functionTemplate->SetClassName(String::New("Console"));
	
	// Create the object template
	
	Local<ObjectTemplate> objectTemplate = functionTemplate->InstanceTemplate();
	objectTemplate->SetInternalFieldCount(1);
	
	// Create an object instance
	
	Local<Object> objectInstance = objectTemplate->NewInstance();
	objectInstance->SetInternalField(0, External::New(this));
	
	// Add functions to object instance
	
	Local<FunctionTemplate> printTemplate = FunctionTemplate::New(print);
	Local<Function> printFunction = printTemplate->GetFunction();
	objectInstance->Set(String::New("print"), printFunction);
	
	Local<FunctionTemplate> inputTemplate = FunctionTemplate::New(input);
	Local<Function> inputFunction = inputTemplate->GetFunction();
	objectInstance->Set(String::New("input"), inputFunction);
	
	return handleScope.Close(objectInstance);
}


Handle<Value> ConsoleObject::print(const Arguments &args)
{
	HandleScope handleScope;
	
	string message;
	
	try
	{
		message = ScriptObject::extractString(args, 0);
	}
	catch (ScriptException &e)
	{
		return e.getException();
	}
	
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
