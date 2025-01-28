cmake_minimum_required(VERSION 3.16)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

message("-- Starting Build")

project(JupitersThrone VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("-- Getting QT components")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

message("-- Adding libs")

add_subdirectory(lib)

include_directories(${CMAKE_SOURCE_DIR})

message("-- Creating Executables")

qt_add_executable(JupitersThrone
    src/main.cpp

    src/engine/consolewindow.h    src/engine/consolewindow.cpp
    src/engine/terminalmanager.h  src/engine/terminalmanager.cpp

    src/game/structures.h
    src/game/constants.h
    src/game/utils/screenmanager.cpp  src/game/utils/screenmanager.h
    src/game/utils/debug.h            src/game/utils/debug.cpp
    src/game/utils/colors.h           src/game/utils/colors.cpp
    src/game/utils/general.h          src/game/utils/general.cpp
    src/game/core/dialougeengine.h    src/game/core/dialougeengine.cpp
    src/game/core/combatengine.h      src/game/core/combatengine.cpp
    src/game/core/game.h              src/game/core/game.cpp
    src/game/core/commandparser.h     src/game/core/commandparser.cpp
)

message("-- Creating UI header")

qt_add_ui(JupitersThrone SOURCES src/engine/consolewindow.ui)

message("-- Linking liberaries")

target_link_libraries(JupitersThrone PRIVATE
    Qt6::Widgets
    LuaCpp
)

set_target_properties(JupitersThrone PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
