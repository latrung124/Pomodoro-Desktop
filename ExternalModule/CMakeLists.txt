# Define paths
# set(PROTOBUF_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../ExternalModule/x64-windows/include)
# set(PROTOBUF_LIB_DIR ${CMAKE_SOURCE_DIR}/../ExternalModule/x64-windows/lib)

# Add the proto generated source and header files
set(PROTO_SRCS ${CMAKE_SOURCE_DIR}/ExternalModule/ServiceProto/Authentication.pb.cc)
set(PROTO_HDRS ${CMAKE_SOURCE_DIR}/ExternalModule/ServiceProto/Authentication.pb.h)

# Include directories
include_directories(${PROTOBUF_INCLUDE_DIR})

# Add library
add_library(ServiceProto SHARED ${PROTO_SRCS} ${PROTO_HDRS})

# Link Protobuf library
target_link_libraries(ServiceProto PRIVATE ${PROTOBUF_LIB_DIR}/libprotobuf.lib)

# Set the output directory for the DLL
set_target_properties(ServiceProto PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
