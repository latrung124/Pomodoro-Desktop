set(HEADERS
    interface/IGatewayService.h
    GatewayService.h)

set(SOURCES
    GatewayService.cpp)

add_library(GatewayService SHARED
    ${HEADERS}
    ${SOURCES})
