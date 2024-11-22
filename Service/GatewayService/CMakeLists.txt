set(HEADERS
    interface/IGatewayService.h
    GatewayService.h)

set(SOURCES
    GatewayService.cpp)

add_library(GatewayService SHARED
    ${PROTO_SRCS}
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(GatewayService PUBLIC
    ${SERVICE_PROTO_DIR}   # for generated protobuf headers
    ${PROTOBUF_INCLUDE_DIR} # for protobuf headers
)

# Link the protobuf library
target_link_libraries(GatewayService PUBLIC
    ${PROTOBUF_LIB_DIR}/libprotobuf.lib
) # Change the .lib file name if needed

