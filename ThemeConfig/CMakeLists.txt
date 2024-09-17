# CMakeLists.txt for ThemeConfig

# Create a library for the ThemeConfig class
add_library(ThemeConfig STATIC
    ThemeConfig.cpp
    ThemeConfig.h
)

# Link necessary Qt libraries
target_link_libraries(ThemeConfig PRIVATE Qt6::Core Qt6::Gui Qt6::Qml)

# Specify include directories
target_include_directories(ThemeConfig PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
