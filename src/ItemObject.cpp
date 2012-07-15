/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "ItemObject.h"
#include "ScriptException.h"

#include <v8.h>

using namespace bit;
using namespace v8;


ItemObject::ItemObject()
{
	printf("ItemObject::ItemObject\n");
}


Local<Object> ItemObject::createInstance()
{
	HandleScope handleScope;
	
	// Create the function template
	
	Local<FunctionTemplate> functionTemplate = FunctionTemplate::New();
	functionTemplate->SetClassName(String::New("Item"));
	
	// Create the object template
	
	Local<ObjectTemplate> objectTemplate = functionTemplate->InstanceTemplate();
	objectTemplate->SetInternalFieldCount(1);
	
	// Create an object instance
	
	Local<Object> objectInstance = objectTemplate->NewInstance();
	objectInstance->SetInternalField(0, External::New(this));
	
	// Add functions to object instance
	
	/*
	Local<FunctionTemplate> printTemplate = FunctionTemplate::New(print);
	Local<Function> printFunction = printTemplate->GetFunction();
	objectInstance->Set(String::New("print"), printFunction);
	
	Local<FunctionTemplate> inputTemplate = FunctionTemplate::New(input);
	Local<Function> inputFunction = inputTemplate->GetFunction();
	objectInstance->Set(String::New("input"), inputFunction);
	*/
	
	return handleScope.Close(objectInstance);
}


Handle<Value> ItemObject::constructor(const Arguments &args)
{
	HandleScope handleScope;
	
	// Make sure the constructor is called with the new keyword
	
	if (!args.IsConstructCall())
	{
		Local<String> message = String::New("Cannot call constructor as a function");
		return ThrowException(Exception::SyntaxError(message));
	}
	
	// Instantiate a new ScriptTemplate
	
	ItemObject *itemObject = new ItemObject();
	Local<Object> itemInstance = itemObject->createInstance();
	itemInstance->SetInternalField(0, External::New(itemObject));
	
	return handleScope.Close(itemInstance);
}
