/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_Application_h
#define BitRPG_Application_h

#include "BitRPG.h"


namespace bit
{
	class Application
	{
	public:
		/**
		 * Instantiates all managers needed in the Application
		 */
		Application();
		
		/**
		 * Starts the application
		 */
		void start();
		
		AssetManagerPtr assetManager;
		ScriptManagerPtr scriptManager;
		DisplayManagerPtr displayManager;
		
	private:
		void initScriptObjects();
		void loadConfig();
	};
}


#endif
