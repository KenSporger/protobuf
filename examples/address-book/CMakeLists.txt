cmake_minimum_required(VERSION 2.6)
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_module)

project(demo)

find_package(ProtoBuf REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/proto)

add_executable(demo     main.cpp 
                        proto/addressbook.pb.cc
            )


target_link_libraries(demo ${PROTOBUF_LIBRARIES} )

