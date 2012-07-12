/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#ifndef BitRPG_Launcher_h
#define BitRPG_Launcher_h

#include <boost/shared_ptr.hpp>

class ContentManager;
class ScriptEngine;
class DisplayManager;


class Launcher
{
public:
	Launcher();
	
	void run();
	
private:
	void loadConfig();
	
	boost::shared_ptr<ContentManager> contentManager;
	boost::shared_ptr<ScriptEngine> scriptEngine;
	boost::shared_ptr<DisplayManager> displayManager;
};

#endif
