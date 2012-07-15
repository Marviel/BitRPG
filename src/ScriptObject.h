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
		virtual v8::Local<v8::Object> createInstance() =0;
		
	protected:
		static bool extractBoolean(const v8::Arguments &args, int index);
		static int64_t extractInteger(const v8::Arguments &args, int index);
		static double extractDouble(const v8::Arguments &args, int index);
		static std::string extractString(const v8::Arguments &args, int index);
		
		/**
		 * Returns a pointer to the ScriptObject instance
		 *
		 * If the functions were registered to the correct ScriptObject,
		 * you can safely static_cast to the derived type.
		 */
		static void *extractHolder(const v8::Arguments &args);
		
	private:
		static v8::Handle<v8::Value> extractArgument(
			const v8::Arguments &args, int index);
	};
}

#endif
