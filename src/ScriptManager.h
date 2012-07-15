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
		
		/**
		 * Adds an instance of an object to the globals in the V8 context
		 */
		void registerObject(ScriptObject *scriptObject, std::string name);
		
		/**
		 * Adds a class constructor to the V8 globals
		 */
		void registerClass(v8::InvocationCallback constructor, std::string name);
		
		/**
		 * Runs a multi-line script in the current V8 context
		 *
		 * This operation is intended for running .js files loaded
		 * by the AssetManager.
		 */
		void runScript(const std::string &source);
		
		/**
		 * Runs a single line of JavaScript
		 *
		 * A command line interface or console should use this function for
		 * executing each line as it it typed.
		 * If the result of the JavaScript statement is not Undefined, its
		 * value is assigned to the temporary "_" variable for use in future
		 * executed statements.
		 */
		std::string evaluate(const std::string &statement);
		
		/**
		 * Parses a JSON string to a structured JSONValue tree
		 */
		JSONValue parseJSON(const std::string &data);
		
		/**
		 * Converts a JSONValue tree structure to a JSON formatted string
		 *
		 * If the pretty variable is true, the output string is formatted
		 * with nice spacing and indention. Otherwise it is condensed into
		 * a minified representation.
		 */
		std::string toJSON(const JSONValue &value, bool pretty = false);
		
		/**
		 * Throws a bit::Exception if a V8 exception has been thrown
		 */
		static void catchException(const v8::TryCatch &tryCatch);
		
	private:
		v8::Persistent<v8::Context> context;
		
		v8::Persistent<v8::Function> jsonParse;
		v8::Persistent<v8::Function> jsonStringify;
	};
}

#endif
