qt_add_executable(JupitersThrone
    main.cpp
)

message("-- Linking Game")

add_subdirectory(engine)
add_subdirectory(game)

target_link_libraries(JupitersThrone PRIVATE
    JupitersThroneEngine
    JupitersThroneGame
    LuaCpp
    Qt6::Widgets
)

set_target_properties(JupitersThrone PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
