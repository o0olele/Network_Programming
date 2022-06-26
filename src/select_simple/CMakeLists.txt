cmake_minimum_required (VERSION 2.6)
project (select)

#包含头文件目录
include_directories( ${PROJECT_SOURCE_DIR}/include )
include_directories( ${PROJECT_SOURCE_DIR}/src )
#添加src子目录，src下的源文件与CMakeLists也会被处理
add_subdirectory( src )

add_executable(server.out server.c)

#链接wrappers库
target_link_libraries(server.out wrappers)
