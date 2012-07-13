/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "JSONValue.h"
#include "Exception.h"

using namespace bit;
using namespace v8;


JSONValue::JSONValue(Local<Value> rootValue)
{
	value = Persistent<Value>::New(rootValue);
}


JSONValue::~JSONValue()
{
	value.Dispose();
}


JSONValue JSONValue::operator[](const char *key)
{
	HandleScope handleScope;
	
	// Check if value is an object
	
	if (!value->IsObject())
		throw bit::Exception("JSONValue is not an object");
	
	Local<Value> valueLocal = Local<Value>::New(value);
	Local<Object> valueObject = Local<Object>::Cast(valueLocal);
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
	
	if (!value->IsArray())
		throw bit::Exception("JSONValue is not an array");
	
	Local<Value> valueLocal = Local<Value>::New(value);
	Local<Array> valueArray = Local<Array>::Cast(valueLocal);
	
	if (valueArray.IsEmpty())
		throw bit::Exception("V8 array could not be created");
	
	// Check if index exists
	
	if (!valueArray->Has(index))
		throw bit::Exception("Index does not exist");
	
	// Return JSONValue
	
	Local<Value> newValue = valueArray->Get(index);
	JSONValue jsonValue(newValue);
	
	return jsonValue;
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


uint32_t JSONValue::arrayLength()
{
	HandleScope handleScope;
	
	Local<Value> valueLocal = Local<Value>::New(value);
	Local<Array> valueArray = Local<Array>::Cast(valueLocal);
	
	if (valueArray.IsEmpty())
		throw bit::Exception("Value is not an array");
	
	uint32_t length = valueArray->Length();
	return length;
}


std::string JSONValue::toString()
{
	//if (!isString() && !isNumber())
	//	throw bit::Exception("Value is not a string");
	
	HandleScope handleScope;
	
	Local<Value> valueLocal = Local<Value>::New(value);
	Local<String> valueString = Local<String>::Cast(valueLocal);
	String::Utf8Value valueUtf(valueString);
	
	return std::string(*valueUtf);
}


int64_t JSONValue::toInteger()
{
	HandleScope handleScope;
	
	Local<Value> valueLocal = Local<Value>::New(value);
	Local<Integer> valueInteger = Local<Integer>::Cast(valueLocal);
	return valueInteger->Value();
}


double JSONValue::toDouble()
{
	HandleScope handleScope;
	
	Local<Value> valueLocal = Local<Value>::New(value);
	Local<Number> valueNumber = Local<Number>::Cast(valueLocal);
	return valueNumber->Value();
}


bool JSONValue::toBoolean()
{
	HandleScope handleScope;
	
	Local<Value> valueLocal = Local<Value>::New(value);
	Local<BooleanObject> valueBoolean = Local<BooleanObject>::Cast(valueLocal);
	return valueBoolean->BooleanValue();
}


