cmake_minimum_required(VERSION 3.5)

project(mcp2515_arduino CXX C ASM)
#include( "arduino.cmake" )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -flto -fno-exceptions" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostartfiles" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -flto" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostartfiles" )
set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto" )

set( ARDUINO_SOURCE "${ARDUINO_ROOT}/hardware/arduino/avr/cores/arduino/")


set(MCP2515_SOURCES mcp2515.cpp)
set(MCP2515_HEADERS 
    ${ARDUINO_ROOT}
    mcp2515.h
    mcp2515-register-map.h
    can-packet.h)

add_library(mcp2515_arduino
    STATIC
    ${MCP2515_SOURCES}
    ${MCP2515_HEADERS})


target_include_directories("${ARDUINO_SOURCE}")