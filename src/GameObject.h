/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_GameObject_h
#define BitRPG_GameObject_h

#include "BitRPG.h"
#include "ScriptObject.h"

#include <boost/shared_ptr.hpp>
#include <v8.h>

class Launcher;


namespace bit
{
	class GameObject : public ScriptObject
	{
	public:
		GameObject();
		
		v8::Local<v8::Object> getObject();
		
		// GameObject specific functions
		
		static v8::Handle<v8::Value> loadMap(const v8::Arguments &args);
		
	private:
		
	};
}

#endif
