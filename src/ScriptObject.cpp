/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "ScriptObject.h"
#include "Exception.h"
#include "ScriptException.h"

using namespace bit;
using namespace v8;
using namespace std;


bool ScriptObject::extractBoolean(const Arguments &args, int index)
{
	HandleScope handleScope;
	TryCatch tryCatch;
	
	// Get Boolean value
	
	Handle<Value> argValue = ScriptObject::extractArgument(args, index);
	
	if (tryCatch.HasCaught())
		return false;
	
	Handle<BooleanObject> argBoolean = Handle<BooleanObject>::Cast(argValue);
	
	if (argBoolean.IsEmpty())
		throw bit::Exception("Argument is not a Boolean object");
	
	return argBoolean->BooleanValue();
}


int64_t ScriptObject::extractInteger(const Arguments &args, int index)
{
	HandleScope handleScope;
	TryCatch tryCatch;
	
	// Get Integer value
	
	Handle<Value> argValue = ScriptObject::extractArgument(args, index);
	
	if (tryCatch.HasCaught())
		return 0;
	
	Handle<Integer> argInteger = Handle<Integer>::Cast(argValue);
	
	if (argInteger.IsEmpty())
		throw bit::Exception("Argument is not an Integer object");
	
	return argInteger->Value();
}


double ScriptObject::extractDouble(const Arguments &args, int index)
{
	HandleScope handleScope;
	TryCatch tryCatch;
	
	// Get Number value
	
	Handle<Value> argValue = ScriptObject::extractArgument(args, index);
	
	if (tryCatch.HasCaught())
		return 0.0;
	
	Handle<Number> argNumber = Handle<Number>::Cast(argValue);
	
	if (argNumber.IsEmpty())
		throw bit::Exception("Argument is not a Number object");
	
	return argNumber->Value();
}


string ScriptObject::extractString(const Arguments &args, int index)
{
	HandleScope handleScope;
	
	// Get String value
	
	Handle<Value> argValue = ScriptObject::extractArgument(args, index);
	Handle<String> argString = Handle<String>::Cast(argValue);
	
	if (argString.IsEmpty())
		throw bit::Exception("Argument is not a String object");
	
	// Create Utf8 encoded string
	
	String::Utf8Value argUtfString(argString);
	
	return string(*argUtfString);
}


Handle<Value> ScriptObject::extractArgument(const Arguments &args, int index)
{
	if (index >= args.Length())
	{
		Local<String> message = String::New("Argument index out of bounds");
		throw ScriptException(v8::Exception::SyntaxError(message));
	}
	
	// Get value
	
	return args[index];
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
