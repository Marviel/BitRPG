/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#ifndef scriptengine_DataObject_h
#define scriptengine_DataObject_h

#include <v8.h>
#include <string>

class ScriptEngine;


class JSONValue
{
public:
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
	
	std::string toString();
	int64_t toInteger();
	double toDouble();
	bool toBoolean();
	
private:
	JSONValue(v8::Local<v8::Value> rootValue);
	
	v8::Local<v8::Value> value;
	
	friend class ScriptEngine;
};


#endif
