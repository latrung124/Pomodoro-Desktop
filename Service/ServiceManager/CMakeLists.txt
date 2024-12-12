set(SM_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/ServiceManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ServiceConcreteHelper.h)

set(SM_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/ServiceManager.cpp)

add_library(ServiceManager STATIC
    ${SERVICE_HEADERS_FILES}
    ${SM_HEADER_FILES}
    ${SM_SOURCE_FILES})

target_include_directories(ServiceManager
    PUBLIC
        ${CMAKE_SOURCE_DIR}/Service
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ServiceManager PUBLIC FirebaseService)
