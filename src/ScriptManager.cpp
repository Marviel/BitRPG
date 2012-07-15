/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "ScriptManager.h"
#include "Exception.h"
#include "JSONValue.h"
#include "ScriptObject.h"

#include <v8.h>
#include <string>
#include <iostream>

using namespace bit;
using namespace v8;
using std::string;


ScriptManager::ScriptManager()
{
	// Init V8
	
	HandleScope handleScope;
	
	context = Context::New();
	context->Enter();
	
	contextScope = new Context::Scope(context);
	Local<Object> global = context->Global();
	
	// Grab the JSON.parse() function
	
	Local<String> JSONString = String::New("JSON");
	Local<Object> JSONObject = Local<Object>::Cast(global->Get(JSONString));
	
	Local<Value> parseValue = JSONObject->Get(String::New("parse"));
	Local<Function> parseFunction = Local<Function>::Cast(parseValue);
	jsonParse = Persistent<Function>::New(parseFunction);
	
	if (jsonParse.IsEmpty() || !jsonParse->IsFunction())
		throw bit::Exception("Could not grab JSON.parse()");
	
	Local<Value> stringifyValue = JSONObject->Get(String::New("stringify"));
	Local<Function> stringifyFunction = Local<Function>::Cast(stringifyValue);
	jsonStringify = Persistent<Function>::New(stringifyFunction);
	
	// The global scope isn't being modified, so we'll comment this out
	
	//context->ReattachGlobal(global);
}


ScriptManager::~ScriptManager()
{
	jsonParse.Dispose();
	jsonStringify.Dispose();
	
	delete contextScope;
	context.Dispose();
}


void ScriptManager::registerObject(ScriptObject *scriptObject, string name)
{
	HandleScope handleScope;
	
	Local<Object> global = context->Global();
	
	// Make the object a global in the V8 context
	
	Local<Object> obj = scriptObject->createInstance();
	global->Set(String::New(name.c_str()), obj);
	
	context->ReattachGlobal(global);
}


void ScriptManager::registerClass(InvocationCallback constructor, std::string name)
{
	HandleScope handleScope;
	
	// Create a V8 function from the constructor callback function
	
	Local<FunctionTemplate> constructorTemplate = FunctionTemplate::New(constructor);
	Local<Function> constructorFunction = constructorTemplate->GetFunction();
	
	// Make the constructor function a global
	
	Local<Object> global = context->Global();
	
	global->Set(String::New(name.c_str()), constructorFunction);
	context->ReattachGlobal(global);
}


void ScriptManager::runScript(const std::string &source)
{
	HandleScope handleScope;
	TryCatch tryCatch;
	
	// Compile script
	
	Local<String> sourceString = String::New(source.c_str());
	Local<Script> script = Script::Compile(sourceString);
	
	catchError(tryCatch);
	
	if (script.IsEmpty())
		throw bit::Exception("Script could not compile");
	
	// Run script
	
	script->Run();
	
	catchError(tryCatch);
}


string ScriptManager::evaluate(const string &statement)
{
	HandleScope handleScope;
	TryCatch tryCatch;
	
	// Compile statement
	
	Local<String> source = String::New(statement.c_str());
	Local<Script> script = Script::Compile(source);
	
	catchError(tryCatch);
	
	if (script.IsEmpty())
		throw bit::Exception("Script did not compile");
	
	// Run script
	
	Handle<Value> result = script->Run();
	
	catchError(tryCatch);
	
	if (result->IsUndefined())
	{
		return string();
	}
	else
	{
		// Assign result value to "_" global variable
		
		Handle<Object> globalObject = context->Global();
		globalObject->Set(String::New("_"), result);
		context->ReattachGlobal(globalObject);
		
		// Return value as string
		
		String::Utf8Value resultUtf(result);
		return string(*resultUtf);
	}
}


JSONValue ScriptManager::parseJSON(const string &data)
{
	if (jsonParse.IsEmpty() || !jsonParse->IsFunction())
		throw bit::Exception("It seems JSON.parse() has disappeared");
	
	HandleScope handleScope;
	TryCatch tryCatch;
	
	// Call the JSON.parse() function
	
	Handle<Value> args[] = { String::New(data.c_str()) };
	Local<Value> result = jsonParse->Call(context->Global(), 1, args);
	
	catchError(tryCatch);
	
	// Contruct root JSONValue
	
	HandleScope returnScope;
	Local<Value> rootValue = handleScope.Close(result);
	return JSONValue(rootValue);
}


string ScriptManager::toJSON(const JSONValue &value)
{
	HandleScope handleScope;
	TryCatch tryCatch;
	
	// Call the JSON.stringify() function
	
	Handle<Value> args[] = { value.value };
	Local<Value> resultValue = jsonStringify->Call(context->Global(), 1, args);
	
	catchError(tryCatch);
	
	// Return string
	
	Local<String> resultString = Local<String>::Cast(resultValue);
	String::Utf8Value resultUtf(resultString);
	return string(*resultUtf);
}


void ScriptManager::catchError(const TryCatch &tryCatch)
{
	// Check if an error has occurred
	
	if (tryCatch.HasCaught())
	{
		HandleScope handleScope;
		
		// Throw an exception with the TryCatch message
		
		Local<Message> message = tryCatch.Message();
		Local<String> messageString = message->Get();
		String::Utf8Value messageUtf(messageString);
		throw bit::Exception(*messageUtf);
	}
}
