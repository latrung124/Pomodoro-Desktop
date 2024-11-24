set(SM_HEADER_FILES
    ServiceManager.h)

set(SM_SOURCE_FILES
    ServiceManager.cpp)

add_library(ServiceManager STATIC
    ${SERVICE_HEADERS_FILES}
    ${SM_HEADER_FILES}
    ${SM_SOURCE_FILES})

target_include_directories(ServiceManager
    PUBLIC
        ${CMAKE_SOURCE_DIR}/Service
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})