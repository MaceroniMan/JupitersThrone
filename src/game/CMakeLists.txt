qt_add_library(JupitersThroneGame STATIC
    structures.h
    utils/screenmanager.cpp
    utils/screenmanager.h
    utils/debug.h utils/debug.cpp
    utils/colors.h utils/colors.cpp
    utils/general.h utils/general.cpp
    core/dialougeengine.h core/dialougeengine.cpp
    core/combatengine.h core/combatengine.cpp
    core/gameloop.h core/gameloop.cpp
)

# Include directories (include the current source directory for header files)
target_include_directories(JupitersThroneGame INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)
