# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.20)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Project definition
project(STM32_Self_Learning)

# Enable CMake support for ASM and C/CPP languages
enable_language(C ASM)

set(BUILD_UNIT_0_NAME STM32_Self_Learning)

# Create an executable object type
add_executable(${BUILD_UNIT_0_NAME}
  Src/nvic.c
  Src/gpio.c)

# STM32CubeIDE for Visual Studio Code managed CMake file
include(cmake/vscode_generated.cmake)

# Compiler options
target_compile_options(${BUILD_UNIT_0_NAME} PRIVATE
  # User defined compiler options
)

# Linker options
target_link_options(${BUILD_UNIT_0_NAME} PRIVATE 
  # User defined linker options
)

# Add sources to executable/library
target_sources(${BUILD_UNIT_0_NAME} PRIVATE
    Src/main.c
    Src/led.c
    Src/clock.c
    Src/timer.c
    Src/button.c
)

# Add include directories
target_include_directories(${BUILD_UNIT_0_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/Inc
)
