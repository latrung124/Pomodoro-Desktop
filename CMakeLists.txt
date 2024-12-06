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
  Utils/CloudUtility/AuthenticationType.h
  Utils/CloudUtility/FirebaseUtility.h

  Controller/BaseController.h
  Controller/SystemController.h
  Controller/ServiceController.h
  Controller/ModuleController/BaseModuleController.h
  Controller/ModuleController/LoginModuleController.h

  Core/Manager/ControllerManager.h
  Core/Helper/ControllerHelper.h
  Core/Helper/Firebase/FirebaseRequestHelper.h
  Core/Helper/Firebase/FirebaseHandlerHelper.h

  Handler/Firebase/FirebaseRequestHandler.h
  Handler/Firebase/FirebaseResponseHandler.h
  Handler/Firebase/MessageProcessor/FirebaseRequestProcessor.h
  Handler/Firebase/MessageProcessor/FirebaseResponseProcessor.h

  Controller/ServiceController.cpp
  Controller/SystemController.cpp
  Controller/ModuleController/LoginModuleController.cpp

  Handler/Firebase/FirebaseRequestHandler.cpp
  Handler/Firebase/FirebaseResponseHandler.cpp
  Handler/Firebase/MessageProcessor/FirebaseRequestProcessor.cpp
  Handler/Firebase/MessageProcessor/FirebaseResponseProcessor.cpp

  Core/Manager/ControllerManager.cpp
)

set(MSVC_RUNTIME_MODE MD)
set(FIREBASE_CPP_SDK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ExternalModule/Third-Parties/firebase_cpp_sdk)
set(firebase_libs firebase_auth firebase_database firebase_firestore firebase_app)
set(ADDITIONAL_LIBS advapi32 ws2_32 crypt32 iphlpapi psapi userenv rpcrt4 ole32 shell32)
add_subdirectory(${FIREBASE_CPP_SDK_DIR} bin/ EXCLUDE_FROM_ALL)

add_subdirectory(ThemeConfig)
add_subdirectory(CommonComponent)
add_subdirectory(HomeScreen)
add_subdirectory(LoginScreen)
add_subdirectory(Service)

target_include_directories(untitled PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(untitled PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    ThemeConfig
    HomeScreenplugin
    LoginScreenplugin

    ServiceManager
)

include(GNUInstallDirs)
install(TARGETS untitled
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
