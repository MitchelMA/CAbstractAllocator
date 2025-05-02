add_library(AbstractAllocator)

file(GLOB PUBLIC_HEADERS  ./include/*.h)
file(GLOB PRIVATE_SOURCES ./private/*.c)

target_sources(AbstractAllocator
    PUBLIC
    ${PUBLIC_HEADERS}
    PRIVATE
    ${PRIVATE_SOURCES})

target_include_directories(AbstractAllocator
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include)
