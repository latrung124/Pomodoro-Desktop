set(HEADERS
    interface/IService.h
    interface/IServiceManager.h

    Manager/ServiceManager.h
)

set(SOURCES
    Manager/ServiceManager.cpp
)

add_library(ServiceManager SHARED
    ${COMMON_SOURCES}
    ${HEADERS}
    ${SOURCES}
)

# Set the output directory for the library
set_target_properties(ServiceManager PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

target_include_directories(ServiceManager PUBLIC
    ${CMAKE_SOURCE_DIR}/Service
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/interface
)

