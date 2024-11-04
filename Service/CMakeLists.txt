set(SERVICEMANAGER_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Service/ServiceManager/interface)

set(COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/Service/ServiceUtils.h
)

add_subdirectory(ServiceManager)
add_subdirectory(GatewayService)

set (SERVICE_PROTO_FILES
    ServiceUsage/api/Gateway/Authentication.proto
)

# Generated files
# set(GENERATED_PROTO_SRCS ${CMAKE_BINARY_DIR})

# Add a custom command to run protoc when the .proto file changes
# add_custom_command(
#     OUTPUT ${GENERATED_PROTO_SRCS}
#     COMMAND protoc --cpp_out=${CMAKE_BINARY_DIR} -I ${SERVICE_PROTO_FILES}
#     MAIN_DEPENDENCY ${SERVICE_PROTO_FILES}
#     COMMENT "Generating C++ source and header from ${SERVICE_PROTO_FILES}"
#     VERBATIM
# )
