
cmake_minimum_required(VERSION 3.10.2)

project("alonegleslearn")

include_directories(include)

aux_source_directory(src native_srcs)

add_library(GLEngine-lib SHARED ${native_srcs} )


find_library(log-lib log )

target_link_libraries(GLEngine-lib  ${log-lib} android EGL GLESv3 m)