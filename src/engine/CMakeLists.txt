# Add the UI file using qt_add_ui() to ensure the header is generated
qt_add_library(JupitersThroneEngine STATIC
    consolewindow.h consolewindow.cpp
    terminalmanager.h terminalmanager.cpp
)

# Automatically handle the .ui file with qt_add_ui() (this should generate the ui_consolewindow.h file)
qt_add_ui(JupitersThroneEngine SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/consolewindow.ui)

# Link QtWidgets library (make sure Qt6 is correctly linked)
target_link_libraries(JupitersThroneEngine PRIVATE Qt6::Widgets)

# Include directories (include the current source directory for header files)
target_include_directories(JupitersThroneEngine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
