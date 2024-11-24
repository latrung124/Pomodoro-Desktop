add_definitions(-DFIREBASE_CONFIG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Resources/Firebase/Config")

set(HEADER_SOURCE_FILES
    FirebaseUtils.h
    Interface/IFirebaseService.h
    Implementation/FirebaseServiceImpl.h
    Implementation/Authentication/FirebaseAuthentication.h
    Implementation/Authentication/AbstractExternalAuthProvider.h
    Implementation/Authentication/AbstractInternalAuthProvider.h
    Implementation/Authentication/EmailPwAuthProvider.h
    Implementation/Authentication/GoogleAuthProvider.h
)

set(SOURCE_FILES
    Implementation/FirebaseServiceImpl.cpp
    Implementation/Authentication/FirebaseAuthentication.cpp
    Implementation/Authentication/EmailPwAuthProvider.cpp
    Implementation/Authentication/GoogleAuthProvider.cpp
)

add_library(FirebaseService
    STATIC
        ${HEADER_SOURCE_FILES}
        ${SOURCE_FILES})

target_include_directories(FirebaseService
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Interface
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Implementation
        ${CMAKE_SOURCE_DIR}/ExternalModule/Third-Parties/Firebase/include)


# Define platform-specific required libraries
if(WIN32)
    set(REQUIRED_LIBS
        advapi32.lib
        ws2_32.lib
        crypt32.lib
    )
elseif(APPLE)
    # For macOS libraries, we still need to use find_library
    set(REQUIRED_LIBS
        pthread
        CoreFoundation
        Foundation
        Security
        GSS
        Kerberos
    )

    # Find macOS libraries
    foreach(LIB ${REQUIRED_LIBS})
        find_library(${LIB}_LIB ${LIB})
        if(NOT ${LIB}_LIB)
            message(FATAL_ERROR "Failed to find ${LIB}")
        endif()
    endforeach()

    # Update REQUIRED_LIBS to use the found library paths
    set(REQUIRED_LIBS
        ${pthread_LIB}
        ${CoreFoundation_LIB}
        ${Foundation_LIB}
        ${Security_LIB}
        ${GSS_LIB}
        ${Kerberos_LIB}
    )
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Set link directories
set(FIREBASE_LIB_DIR
    ${CMAKE_SOURCE_DIR}/ExternalModule/Third-Parties/Firebase/MT/Debug)

target_link_libraries(FirebaseService
    PUBLIC
    ${FIREBASE_LIB_DIR}/firebase_auth.lib
    ${FIREBASE_LIB_DIR}/firebase_app.lib)