/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_ScriptObject_h
#define BitRPG_ScriptObject_h

#include <v8.h>
#include <string>


namespace bit
{
	class ScriptObject
	{
	public:
		virtual v8::Local<v8::Object> getObject() =0;
		
	protected:
		v8::Local<v8::Object> getEmptyObject();
		
		static void extractArguments(const v8::Arguments &args, std::string format, ...);
		static void *getThis(const v8::Arguments &args);
	};
}

#endif
