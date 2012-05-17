/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#ifndef SCRIPTENGINE_H_
#define SCRIPTENGINE_H_

#include <boost/shared_ptr.hpp>
#include <v8.h>
#include <string>

class ContentManager;
class JSONValue;


/**
 * Manages the scripting engine
 *
 * Today's scripting engine is... JavaScript V8!
 */
class ScriptEngine
{
public:
	ScriptEngine();
	~ScriptEngine();
	
	std::string evaluate(const std::string &statement);
	JSONValue parseJSON(const std::string &data);
	std::string toJSON(const JSONValue &value);
	
private:
	std::string getErrorMessage(v8::TryCatch &tryCatch);
	
	v8::Persistent<v8::Context> context;
	v8::Context::Scope *contextScope;
	
	v8::Local<v8::Function> jsonParse;
	v8::Local<v8::Function> jsonStringify;
};


#endif
