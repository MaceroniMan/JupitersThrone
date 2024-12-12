cmake_minimum_required(VERSION 3.9)
project(LuaLang)

set(CMAKE_CXX_STANDARD 17)

message("-- Linking Lua Language")

file(GLOB LUA_FILES
    "*.h"
    "*.c"
)

qt_add_library(LuaLang STATIC
    ${LUA_FILES}
)

#target_link_libraries(lua ${CMAKE_SOURCE_DIR}/lib/lua/lua54.a)

target_include_directories(LuaLang INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
