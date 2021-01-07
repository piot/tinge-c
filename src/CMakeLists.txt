cmake_minimum_required(VERSION 3.17)
project(tinge-example C)

set(CMAKE_C_STANDARD 99)

set(deps ../deps/)

include_directories(${deps}tiny-libc/src/include) # needed from flood-c
include_directories(${deps}flood-c/src/include)
include_directories(${deps}clog/src/include)
include_directories(include)

file(GLOB_RECURSE deps_src FOLLOW_SYMLINKS
        "${deps}*/src/lib/*.c"
        )

file(GLOB_RECURSE lib_src FOLLOW_SYMLINKS
        "lib/*.c"
        )

add_executable(tinge-example
    ${deps_src}
    ${lib_src}
    examples/main.c
)
target_link_libraries(tinge-example m)