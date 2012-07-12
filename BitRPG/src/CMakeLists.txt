
add_executable(BitRPG
	main.cpp
	BitRPG.h
	Exception.cpp Exception.h
#	Application.cpp Application.h
	AssetManager.cpp AssetManager.h
#	ScriptManager.cpp ScriptManager.h
#	ScriptObject.cpp ScriptObject.h
#	DisplayManager.cpp DisplayManager.h
#	StateManager.cpp StateManager.h
#	Entity.cpp Entity.h
#	GameObject.cpp GameObject.h
#	JSONValue.cpp JSONValue.h
#	MapLayer.cpp MapLayer.h
#	MapManager.cpp MapManager.h
#	MapTile.h
)


target_link_libraries(BitRPG ${SFML_LIBRARIES})
target_link_libraries(BitRPG ${V8_LIBRARIES})
