/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "ScriptObject.h"
#include "Exception.h"

#include <stdarg.h>
#include <sstream>
#include <string>

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


/*
void ScriptObject::extractArguments(const Arguments &args, const string format, ...)
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
		
		// 32-bit integer
		
		if (type == 'i')
		{
			if (!argument->IsInt32())
				throw bit::Exception("Argument is not an integer");
			
			Local<Integer> intArgument = Local<Integer>::Cast(argument);
			
			int32_t *val = va_arg(va, int32_t *);
			*val = intArgument->Int32Value();
		}
		
		// Double floating point
		
		else if (type == 'f')
		{
			Local<Number> floatArgument = Local<Number>::Cast(argument);
			
			if (floatArgument.IsEmpty())
				throw bit::Exception("Argument is not a float");
			
			double *val = va_arg(va, double *);
			*val = floatArgument->NumberValue();
		}
		
		// C++ string
		
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
*/


bool ScriptObject::extractBoolean(const Arguments &args, int index)
{
	HandleScope handleScope;
	
	// Get Boolean value
	
	Local<Value> argValue = ScriptObject::extractArgument(args, index);
	Local<BooleanObject> argBoolean = Local<BooleanObject>::Cast(argValue);
	
	if (argBoolean.IsEmpty())
		throw new bit::Exception("Argument is not a Boolean object");
	
	return argBoolean->BooleanValue();
}


int64_t ScriptObject::extractInteger(const Arguments &args, int index)
{
	HandleScope handleScope;
	
	// Get Integer value
	
	Local<Value> argValue = ScriptObject::extractArgument(args, index);
	Local<Integer> argInteger = Local<Integer>::Cast(argValue);
	
	if (argInteger.IsEmpty())
		throw new bit::Exception("Argument is not an Integer object");
	
	return argInteger->Value();
}


double ScriptObject::extractDouble(const Arguments &args, int index)
{
	HandleScope handleScope;
	
	// Get Number value
	
	Local<Value> argValue = ScriptObject::extractArgument(args, index);
	Local<Number> argNumber = Local<Number>::Cast(argValue);
	
	if (argNumber.IsEmpty())
		throw new bit::Exception("Argument is not a Number object");
	
	return argNumber->Value();
}


string ScriptObject::extractString(const Arguments &args, int index)
{
	HandleScope handleScope;
	
	// Get String value
	
	Local<Value> argValue = ScriptObject::extractArgument(args, index);
	Local<String> argString = Local<String>::Cast(argValue);
	
	if (argString.IsEmpty())
		throw new bit::Exception("Argument is not a String object");
	
	// Create Utf8 encoded string
	
	String::Utf8Value argUtfString(argString);
	
	return string(*argUtfString);
}


void *ScriptObject::extractHolder(const Arguments &args)
{
	HandleScope handleScope;
	
	// Extract first internal field from Argument's holder object
	
	Local<Object> holderObject = args.Holder();
	Local<Value> holderValue = holderObject->GetInternalField(0);
	
	if (holderValue.IsEmpty())
		throw bit::Exception("No internal fields found in holder object");
	
	if (!holderValue->IsExternal())
		throw bit::Exception("The first field of holder object is not an ExternalObject");
	
	// Extract void pointer
	
	void *holderPointer = External::Unwrap(holderValue);
	
	if (holderPointer == NULL)
		throw bit::Exception("Extracted pointer is null");
	
	return holderPointer;
}


Local<Value> ScriptObject::extractArgument(const Arguments &args, int index)
{
	if (index >= args.Length())
		throw new bit::Exception("Argument index out of bounds");
	
	// Get value
	
	return args[index];
}
