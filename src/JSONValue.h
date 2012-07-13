/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef scriptengine_DataObject_h
#define scriptengine_DataObject_h

#include "BitRPG.h"
#include <v8.h>
#include <string>


namespace bit
{
	class JSONValue
	{
	public:
		~JSONValue();
		
		/**
		 * Accesses a value specified by the key
		 *
		 * This operation is only valid for objects.
		 */
		JSONValue operator[](const char *key);
		
		/**
		 * Accesses a value specified by an integer index
		 */
		JSONValue operator[](int index);
		
		bool isArray();
		bool isBoolean();
		bool isNumber();
		bool isObject();
		bool isString();
		
		uint32_t arrayLength();
		
		std::string toString();
		int64_t toInteger();
		double toDouble();
		bool toBoolean();
		
	private:
		friend class ScriptManager;
		JSONValue(v8::Local<v8::Value> rootValue);
		
		v8::Persistent<v8::Value> value;
	};
}

#endif
