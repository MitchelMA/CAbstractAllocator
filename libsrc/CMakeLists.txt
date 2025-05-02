add_library(Allocator)

file(GLOB PUBLIC_HEADERS  ./include/*.h)
file(GLOB PRIVATE_SOURCES ./private/*.c)

target_sources(Allocator
    PUBLIC
    ${PUBLIC_HEADERS}
    PRIVATE
    ${PRIVATE_SOURCES})

target_include_directories(Allocator
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include)
