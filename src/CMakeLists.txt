
# SFML library

find_package(SFML 2 REQUIRED COMPONENTS system window graphics)

include_directories(${SFML_INCLUDE_DIR})
#link_directories(${SFML_LIBRARIES})

# V8 library

find_package(V8 REQUIRED)

include_directories(${V8_INCLUDE_DIR})
#link_directories(${V8_LIBRARIES})


# BitRPG executable

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
