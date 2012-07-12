
# SFML library

find_package(SFML 2 COMPONENTS system window graphics REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARIES})

# V8 library

find_package(V8 REQUIRED)

include_directories(${V8_INCLUDE_DIR})
link_directories(${V8_LIBRARIES})

# Source files

add_subdirectory(src)
add_subdirectory(test)
