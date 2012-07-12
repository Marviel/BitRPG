/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#include "JSONValue.h"
#include "Exception.h"

using namespace v8;


JSONValue::JSONValue(Local<Value> rootValue)
{
	value = rootValue;
}


JSONValue JSONValue::operator[](const char *key)
{
	HandleScope handleScope;
	
	// Check if value is an object
	
	if (!value->IsObject())
		throw bit::Exception("JSONValue is not an object");
	
	Local<Object> valueObject = Local<Object>::Cast(value);
	Local<String> keyString = String::New(key);
	
	// Check if key exists
	
	if (!valueObject->Has(keyString))
		throw bit::Exception("Key '" + std::string(key) + "' does not exist");
	
	// Return JSONValue
	
	Local<Value> newValue = handleScope.Close(valueObject->Get(keyString));
	return JSONValue(newValue);
}


JSONValue JSONValue::operator[](int index)
{
	HandleScope handleScope;
	
	// Check if value is an array
	
	if (!value->IsObject())
		throw bit::Exception("JSONValue is not an array");
	
	Local<Object> valueObject = Local<Object>::Cast(value);
	
	// Check if index exists
	
	if (!valueObject->Has(index))
		throw bit::Exception("Index does not exist");
	
	// Return JSONValue
	
	Local<Value> newValue = handleScope.Close(valueObject->Get(index));
	return JSONValue(newValue);
}


bool JSONValue::isArray()
{
	return value->IsArray();
}


bool JSONValue::isBoolean()
{
	// The second term here may be redundant.
	// Does IsBoolean() return true for BooleanObjects?
	
	return value->IsBoolean() || value->IsBooleanObject();
}


bool JSONValue::isNumber()
{
	return value->IsNumber();
}


bool JSONValue::isObject()
{
	return value->IsObject();
}


bool JSONValue::isString()
{
	return value->IsString();
}


std::string JSONValue::toString()
{
	//if (!isString() && !isNumber())
	//	throw bit::Exception("Value is not a string");
	
	HandleScope handleScope;
	
	Handle<String> valueString = Handle<String>::Cast(value);
	String::Utf8Value valueUtf(valueString);
	
	return std::string(*valueUtf);
}


int64_t JSONValue::toInteger()
{
	HandleScope handleScope;
	
	Local<Integer> valueInteger = Local<Integer>::Cast(value);
	return valueInteger->Value();
}


double JSONValue::toDouble()
{
	HandleScope handleScope;
	
	Local<Number> valueNumber = Local<Number>::Cast(value);
	return valueNumber->Value();
}


bool JSONValue::toBoolean()
{
	HandleScope handleScope;
	
	Local<BooleanObject> valueBoolean = Local<BooleanObject>::Cast(value);
	return valueBoolean->BooleanValue();
}


