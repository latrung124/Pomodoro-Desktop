cmake_minimum_required(VERSION 3.16)

project(untitled LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_standard_project_setup(REQUIRES 6.5)

# Add resources.qrc
qt6_add_resources(APP_RESOURCES resources.qrc)

qt_add_executable(untitled
  main.cpp
  ${APP_RESOURCES}
  Utils/CommonSettingsDefine.h
  Controller/SystemController.h

  Controller/SystemController.cpp
)

add_subdirectory(ThemeConfig)

add_subdirectory(CommonComponent)
add_subdirectory(HomeScreen)
add_subdirectory(LoginScreen)

target_link_libraries(untitled PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    ThemeConfig
    HomeScreenplugin
    LoginScreenplugin
    )

include(GNUInstallDirs)
install(TARGETS untitled
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
