/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#include "ScriptEngine.h"
#include "Exception.h"
#include "JSONValue.h"

#include <v8.h>
#include <string>

using namespace v8;
using std::string;


ScriptEngine::ScriptEngine()
{
	HandleScope handleScope;
	
	context = Context::New();
	contextScope = new Context::Scope(context);
	Local<Object> global = context->Global();
	
	// Grab the JSON.parse() function
	
	Local<String> JSONString = String::New("JSON");
	Local<Object> JSONObject = Local<Object>::Cast(global->Get(JSONString));
	
	Local<Value> parseValue = JSONObject->Get(String::New("parse"));
	jsonParse = Local<Function>::Cast(parseValue);
	
	Local<Value> stringifyValue = JSONObject->Get(String::New("stringify"));
	jsonStringify = Local<Function>::Cast(stringifyValue);
	
	//context->ReattachGlobal(global);
}


ScriptEngine::~ScriptEngine()
{
	delete contextScope;
	context.Dispose();
}


string ScriptEngine::evaluate(const string &statement)
{
	HandleScope handleScope;
	TryCatch tryCatch;
	
	// Compile statement
	
	Handle<String> source = String::New(statement.c_str());
	Handle<Script> script = Script::Compile(source);
	
	if (tryCatch.HasCaught())
		return getErrorMessage(tryCatch);
	
	else if (script.IsEmpty())
		throw bit::Exception("Script did not compile");
	
	// Run script
	
	Handle<Value> result = script->Run();
	
	if (tryCatch.HasCaught())
		return getErrorMessage(tryCatch);
	
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


JSONValue ScriptEngine::parseJSON(const string &data)
{
	HandleScope handleScope;
	TryCatch tryCatch;
	
	// Call the JSON.parse() function
	
	Handle<Value> args[] = { String::New(data.c_str()) };
	Local<Value> result = jsonParse->Call(context->Global(), 1, args);
	
	if (tryCatch.HasCaught())
		throw bit::Exception(getErrorMessage(tryCatch));
	
	// Contruct root JSONValue
	
	HandleScope returnScope;
	Local<Value> rootValue = handleScope.Close(result);
	return JSONValue(rootValue);
}


string ScriptEngine::toJSON(const JSONValue &value)
{
	HandleScope handleScope;
	TryCatch tryCatch;
	
	// Call the JSON.stringify() function
	
	Handle<Value> args[] = { value.value };
	Local<Value> resultValue = jsonStringify->Call(context->Global(), 1, args);
	
	if (tryCatch.HasCaught())
		throw bit::Exception(getErrorMessage(tryCatch));
	
	// Return string
	
	Local<String> resultString = Local<String>::Cast(resultValue);
	String::Utf8Value resultUtf(resultString);
	return string(*resultUtf);
}


string ScriptEngine::getErrorMessage(TryCatch &tryCatch)
{
	HandleScope handleScope;
	
	Handle<Message> message = tryCatch.Message();
	String::Utf8Value utfMessage(message->Get());
	
	// Construct string output
	
	string output = *utfMessage;
	
	return output;
}


