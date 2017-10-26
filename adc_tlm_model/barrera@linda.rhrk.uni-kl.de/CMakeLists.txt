cmake_minimum_required (VERSION 2.8)
project (exercise3)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-files)
# output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

IF(APPLE)
list(APPEND CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -DDEBUG")
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
list(APPEND CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -std=c++0x")
ENDIF()

find_package(PkgConfig REQUIRED)
find_package(SystemC REQUIRED)
find_package(SystemCAMS REQUIRED)

include_directories(${SYSTEMC_INCLUDE_DIRS} ${SYSTEMCAMS_INCLUDE_DIRS} ${SICYPHOS_INCLUDE_DIRS})
add_definitions(-D DEBUG)

#add_subdirectory(src)
#add_subdirectory(include)
add_subdirectory(tb)
add_subdirectory(sw)
