/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_ScriptManager_h
#define BitRPG_ScriptManager_h

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
		void registerClass(v8::InvocationCallback constructor, std::string name);
		
		void runScript(const std::string &source);
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
