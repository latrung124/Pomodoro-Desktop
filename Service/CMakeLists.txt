
set(SERVICE_HEADERS_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/IBaseService.h
    ${CMAKE_CURRENT_SOURCE_DIR}/IBaseServiceListener.h
)

add_subdirectory(ServiceManager)
add_subdirectory(FirebaseService)