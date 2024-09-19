# CMakeLists.txt for ThemeConfig

set(CMAKE_AUTORCC ON)
# Add resources.qrc
qt6_add_resources(THEME_RESOURCES ThemeResources.qrc)

# Create a library for the ThemeConfig class
add_library(ThemeConfig STATIC
    ${THEME_RESOURCES}
    Utils/ThemeDefined.h
    ThemeConfig.h
    
    ThemeConfig.cpp
)

# Link necessary Qt libraries
target_link_libraries(ThemeConfig PRIVATE Qt6::Core Qt6::Gui Qt6::Qml)

# Specify include directories
target_include_directories(ThemeConfig PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
