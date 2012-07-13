/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef ScriptManager_H_
#define ScriptManager_H_

#include "BitRPG.h"

#include <v8.h>
#include <string>


namespace bit
{
	/**
	 * Manages the scripting engine
	 *
	 * Today's scripting engine is... JavaScript V8!
	 */
	class ScriptManager
	{
	public:
		ScriptManager();
		~ScriptManager();
		
		void registerObject(ScriptObject *scriptObject, std::string name);
		
		std::string evaluate(const std::string &statement);
		JSONValue parseJSON(const std::string &data);
		std::string toJSON(const JSONValue &value);
		
		static void catchError(const v8::TryCatch &tryCatch);
		
	private:
		v8::Persistent<v8::Context> context;
		v8::Context::Scope *contextScope;
		
		v8::Persistent<v8::Function> jsonParse;
		v8::Persistent<v8::Function> jsonStringify;
	};
}

#endif
