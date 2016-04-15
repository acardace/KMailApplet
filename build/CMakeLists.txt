cmake_minimum_required (VERSION 2.6)
project (MailApplet)

#location options
SET(EXECUTABLE_OUTPUT_PATH ../)

# gcc flags
SET(CMAKE_CXX_FLAGS "--std=c++11 -g")

#includes
include_directories(../include)

#source files
FILE(GLOB_RECURSE SOURCES ../src/*.cpp)

add_executable(MailApplet ${SOURCES})
