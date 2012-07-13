/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "ScriptObject.h"
#include "Exception.h"

#include <stdarg.h>
#include <sstream>

using namespace bit;
using namespace v8;
using namespace std;


Local<Object> ScriptObject::getEmptyObject()
{
	HandleScope handleScope;
	
	// Build template
	
	Local<ObjectTemplate> instanceTemplate = ObjectTemplate::New();
	instanceTemplate->SetInternalFieldCount(1);
	
	// Build object
	
	Local<Object> obj = instanceTemplate->NewInstance();
	obj->SetInternalField(0, External::New(this));
	
	return handleScope.Close(obj);
}


void ScriptObject::extractArguments(const Arguments &args, string format, ...)
{
	int argLength = args.Length();
	
	// Check for equal number of arguments
	
	if (argLength != format.length())
	{
		std::stringstream message;
		message << "Incorrect number of arguments when calling ";
		
		String::Utf8Value callee(args.Callee()->GetName());
		message << *callee << "()\n";
		
		message << "Expected " << format.length();
		message << ", got " << argLength;
		
		throw bit::Exception(message.str());
	}
	
	// Prepare for iteration
	
	va_list va;
	va_start(va, format);
	
	HandleScope handleScope;
	
	// Iterate through each argument and character in format specification
	
	for (int i = 0; i < argLength; ++i)
	{
		char type = format.at(i);
		Local<Value> argument = args[i];
		
		// Integer
		
		if (type == 'i')
		{
			if (!argument->IsInt32())
				throw bit::Exception("Argument is not an integer");
			
			Local<Integer> intArgument = Local<Integer>::Cast(argument);
			
			int32_t *val = va_arg(va, int32_t *);
			*val = intArgument->Int32Value();
		}
		
		// Float
		
		else if (type == 'f')
		{
			Local<Number> floatArgument = Local<Number>::Cast(argument);
			
			if (floatArgument.IsEmpty())
				throw bit::Exception("Argument is not a float");
			
			double *val = va_arg(va, double *);
			*val = floatArgument->NumberValue();
		}
		
		// String
		
		else if (type == 's')
		{
			Local<String> stringArgument = Local<String>::Cast(argument);
			
			if (stringArgument.IsEmpty())
				throw bit::Exception("Argument is not a string");
			
			String::Utf8Value utfArgument(stringArgument);
			string *val = va_arg(va, string *);
			*val = *utfArgument;
		}
	}
}


void *ScriptObject::getThis(const Arguments &args)
{
	HandleScope handleScope;
	
	// Extract first internal field from Argument's holder object
	
	Local<Object> holderObject = args.Holder();
	Local<Value> thisValue = holderObject->GetInternalField(0);
	
	if (thisValue.IsEmpty())
		throw bit::Exception("No internal fields found in holder object");
	
	if (!thisValue->IsExternal())
		throw bit::Exception("The first field of holder object is not an ExternalObject");
	
	// Extract void pointer
	
	void *thisPointer = External::Unwrap(thisValue);
	
	if (thisPointer == NULL)
		throw bit::Exception("Extracted pointer is null");
	
	return thisPointer;
}


