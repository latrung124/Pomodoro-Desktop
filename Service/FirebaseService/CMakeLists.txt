set(HEADER_SOURCE_FILES
    FirebaseUtils.h
    Interface/IFirebaseService.h
    Implementation/FirebaseServiceImpl.h
)

set(SOURCE_FILES
    Implementation/FirebaseServiceImpl.cpp
)

add_library(FirebaseService STATIC ${HEADER_SOURCE_FILES} ${SOURCE_FILES})

target_include_directories(FirebaseService
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Interface
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Implementation)
