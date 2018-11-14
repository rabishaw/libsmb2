cmake_minimum_required (VERSION 2.8)
project (libsmb2++)

#switch this ON to build shared library
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(ENABLE_EXAMPLES "Build example programs" ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -O2 -fshort-wchar -Werror -Wno-unused-but-set-variable -Wno-strict-aliasing -Wno-narrowing")

#not sure if it should be here
add_definitions(-D_REENTRANT -DR_LINUX_3 -D_POSIX_PTHREAD_SEMANTICS -D_GNU_SOURCE=1)

#get the target architecture
# each output has a '\n' which needs to be truncated
EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE MARCH)
EXECUTE_PROCESS( COMMAND uname -s COMMAND awk "{ print tolower($$1) }" COMMAND tr -d '\n' OUTPUT_VARIABLE OS)
set(ARCH ${MARCH}-${OS})

message("Build Architecture = " ${ARCH})

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/smb2")

add_subdirectory (lib)
if(ENABLE_EXAMPLES)
  add_subdirectory(examples)
endif()
