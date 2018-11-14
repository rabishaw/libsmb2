cmake_minimum_required (VERSION 2.6)
project (libsmb2++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set the directory paths
#set(RF_ROOT "$ENV{RF_ROOT}")
#set(RF_COMMON          "${RF_ROOT}/common")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -O2 -fshort-wchar -Werror -Wno-unused-but-set-variable -Wno-strict-aliasing")

#not sure if it should be here
add_definitions(-D_REENTRANT -DR_LINUX_3 -D_POSIX_PTHREAD_SEMANTICS -D_GNU_SOURCE=1)

#get the target architecture
# each output has a '\n' which needs to be truncated
EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE MARCH)
EXECUTE_PROCESS( COMMAND uname -s COMMAND awk "{ print tolower($$1) }" COMMAND tr -d '\n' OUTPUT_VARIABLE OS)
set(ARCH ${MARCH}-${OS})

message( "Architecture = " ${ARCH} )

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/smb2")

set(LINUX_KERNEL_SOURCE_DIR "/usr/src/kernels/${LINUX_KERNEL_VERSION}-${MACH}")

EXECUTE_PROCESS(COMMAND xml2-config "--cflags" COMMAND sed "s/^.\\{2\\}//g" COMMAND tr -d '\n' OUTPUT_VARIABLE var)
set(LIBXML2_INCLUDES ${var})

EXECUTE_PROCESS(COMMAND xml2-config "--libs" COMMAND sed "s/-l//g" COMMAND tr -d '\n' OUTPUT_VARIABLE var2)
set(LIBXML2_LIBS ${var2})

add_subdirectory (lib)
