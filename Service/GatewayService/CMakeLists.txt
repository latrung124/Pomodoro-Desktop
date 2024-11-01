set(HEADERS
    interface/IGatewayService.h
    interface/IGatewayServiceApiSender.h
    interface/IGatewayServiceApiReceiver.h

    MessageHandler/ClientMessageQueueHandler.h
    MessageHandler/ServerMessageQueueHandler.h

    MessageProcessor/ClientMessageProcessor.h
    MessageProcessor/ServerMessageProcessor.h

    GatewayService.h)

set(SOURCES
    GatewayService.cpp
    GatewayServiceApiSender.cpp
    GatewayServiceApiReceiver.cpp

    MessageHandler/ClientMessageQueueHandler.cpp
    MessageHandler/ServerMessageQueueHandler.cpp

    MessageProcessor/ClientMessageProcessor.cpp
    MessageProcessor/ServerMessageProcessor.cpp
)

add_library(GatewayService SHARED
    ${PROTO_SRCS}
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(GatewayService PUBLIC
    ${SERVICE_PROTO_DIR}   # for generated protobuf headers
    ${PROTOBUF_INCLUDE_DIR} # for protobuf headers
    ${CMAKE_CURRENT_SOURCE_DIR} # for GatewayService.h
    ${CMAKE_CURRENT_SOURCE_DIR}/interface # for IGatewayService.h
)

# Link the protobuf library
target_link_libraries(GatewayService PUBLIC
    ${PROTOBUF_LIB_DIR}/libprotobuf.lib
) # Change the .lib file name if needed

