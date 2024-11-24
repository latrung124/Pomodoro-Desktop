cmake_minimum_required(VERSION 3.27.7)

project(untitled LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GenerateExportHeader)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(untitled
  main.cpp

  Utils/CommonSettingsDefine.h
  Controller/SystemController.h
  Controller/ModuleController/BaseModuleController.h
  Controller/ModuleController/LoginModuleController.h

  Controller/SystemController.cpp
  Controller/ModuleController/LoginModuleController.cpp
)

add_subdirectory(ThemeConfig)
add_subdirectory(CommonComponent)
add_subdirectory(HomeScreen)
add_subdirectory(LoginScreen)
add_subdirectory(Service)

target_link_libraries(untitled PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    ThemeConfig
    HomeScreenplugin
    LoginScreenplugin

    FirebaseService
)

include(GNUInstallDirs)
install(TARGETS untitled
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
