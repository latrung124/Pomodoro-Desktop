add_definitions(-DFIREBASE_CONFIG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Resources/Firebase/Config")

set(FS_HEADER_FILES
    FirebaseUtils.h
    Interface/IFirebaseService.h
    Interface/IFirebaseAuthListener.h
    Implementation/FirebaseHelper.h
    Implementation/FirebaseApp.h
    Implementation/FirebaseConfig.h
    Implementation/FirebaseServiceImpl.h
    Implementation/FirebasePayloadFactory.h
    Implementation/FirebaseListenerManager.h
    Implementation/Authentication/FirebaseAuthentication.h
    Implementation/Authentication/AbstractExternalAuthProvider.h
    Implementation/Authentication/AbstractInternalAuthProvider.h
    Implementation/Authentication/EmailPwAuthProvider.h
    Implementation/Authentication/GoogleAuthProvider.h
    Implementation/FirebaseGateway/FirebaseSender.h
    Implementation/FirebaseGateway/FirebaseGatewayManager.h
    Implementation/FirebaseGateway/AuthWrapper.h
    Implementation/FirebaseGateway/OAuthWrapper.h
    Implementation/FirebaseGateway/GoogleOAuthWrapper.h
    Implementation/Listener/FirebaseAuthListenerImpl.h
)

set(FS_SOURCE_FILES
    Implementation/FirebaseApp.cpp
    Implementation/FirebaseConfig.cpp
    Implementation/FirebaseServiceImpl.cpp
    Implementation/FirebasePayloadFactory.cpp
    Implementation/FirebaseListenerManager.cpp
    Implementation/Authentication/FirebaseAuthentication.cpp
    Implementation/Authentication/EmailPwAuthProvider.cpp
    Implementation/Authentication/GoogleAuthProvider.cpp
    Implementation/FirebaseGateway/FirebaseSender.cpp
    Implementation/FirebaseGateway/FirebaseGatewayManager.cpp
    Implementation/FirebaseGateway/AuthWrapper.cpp
    Implementation/FirebaseGateway/GoogleOAuthWrapper.cpp
    Implementation/Listener/FirebaseAuthListenerImpl.cpp
)

add_library(FirebaseService
    STATIC
        ${SERVICE_HEADERS_FILES}
        ${FS_HEADER_FILES}
        ${FS_SOURCE_FILES})

target_include_directories(FirebaseService
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Interface
        ${CMAKE_SOURCE_DIR}/Service
        ${CMAKE_CURRENT_SOURCE_DIR}/Implementation
        ${CMAKE_SOURCE_DIR})

# Set link directories
target_link_libraries(FirebaseService
    PUBLIC
    Qt6::Core
    Qt6::Network
    Qt6::Gui
    Qt6::NetworkAuth)
