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

# Define paths
set(SERVICE_PROTO_DIR ${CMAKE_SOURCE_DIR}/ExternalModule/ServiceProto)
set(PROTOBUF_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/ExternalModule/x64-windows/include)
set(PROTOBUF_LIB_DIR ${CMAKE_SOURCE_DIR}/ExternalModule/x64-windows/lib)

# Add the proto generated source and header files
set(PROTO_SRCS ${SERVICE_PROTO_DIR}/Authentication.pb.cc)
set(PROTO_HDRS ${SERVICE_PROTO_DIR}/Authentication.pb.h)

add_executable(untitled
  main.cpp

  Utils/CommonSettingsDefine.h
  Controller/SystemController.h
  Controller/ModuleController/BaseModuleController.h
  Controller/ModuleController/LoginModuleController.h

  Controller/SystemController.cpp
  Controller/ModuleController/LoginModuleController.cpp
)

add_subdirectory(ThemeConfig)

#add qml module subdirectories
add_subdirectory(CommonComponent)
add_subdirectory(HomeScreen)
add_subdirectory(LoginScreen)
add_subdirectory(ExternalModule)

#add service subdirectory
add_subdirectory(Service)

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

install(DIRECTORY ${SERVICE_PROTO_DIR} DESTINATION include)
