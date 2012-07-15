/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "ScriptException.h"

using namespace bit;
using namespace v8;


ScriptException::ScriptException(Handle<Value> exception)
{
	this->exception = Persistent<Value>::New(exception);
	
	// Throw the exception to V8's exception stack
	
	ThrowException(exception);
}


ScriptException::~ScriptException()
{
	exception.Dispose();
}


Local<Value> ScriptException::getException()
{
	HandleScope handleScope;
	
	Local<Value> exceptionLocal = Local<Value>::New(exception);
	return handleScope.Close(exceptionLocal);
}
