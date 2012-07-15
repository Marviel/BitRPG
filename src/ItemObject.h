/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_ItemObject_h
#define BitRPG_ItemObject_h

#include "BitRPG.h"
#include "ScriptObject.h"
#include <v8.h>


namespace bit
{
	class ItemObject : public ScriptObject
	{
	public:
		ItemObject();
		
		v8::Local<v8::Object> createInstance();
		static v8::Handle<v8::Value> constructor(const v8::Arguments &args);
	};
}


#endif
