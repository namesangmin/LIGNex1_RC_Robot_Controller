cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME LIGNex1_RC_Robot_Controller)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C CXX ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# 블루투스 파일 - GLOB으로 전부 추가
file(GLOB_RECURSE BLE_SOURCES
    ${PROJECT_SOURCE_DIR}/Drivers/Ble/Src/*.cpp
)
file(GLOB_RECURSE CONTROLLER_SOURCES
    ${PROJECT_SOURCE_DIR}/App/Controller/*cpp  
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here

    # tasks header paths
    ${PROJECT_SOURCE_DIR}/App/Tasks/BluetoothRxTask/Src/BluetoothRxTask.cpp
    ${PROJECT_SOURCE_DIR}/App/Tasks/InputTask/Src/InputTask.cpp

    # Interrupt header path
    ${PROJECT_SOURCE_DIR}/App/ISR/Src/Interrupts.cpp

        # 컨트롤러 부분 폴더
    # ${PROJECT_SOURCE_DIR}/App/Controller/Manager/Src/SystemManager.cpp
    # ${PROJECT_SOURCE_DIR}/App/Controller/Modules/Src/JoyStickController.cpp
    # ${PROJECT_SOURCE_DIR}/App/Controller/Modules/Src/ServoController.cpp
 
    # 블루투스
    ${BLE_SOURCES}
    ${CONTROLLER_SOURCES}
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths

    # tasks header paths
    ${PROJECT_SOURCE_DIR}/App/Tasks/BluetoothRxTask/Inc
    ${PROJECT_SOURCE_DIR}/App/Tasks/InputTask/Inc

    # Interrupt header path
    ${PROJECT_SOURCE_DIR}/App/ISR/Inc

    # 컨트롤러 경로
    ${PROJECT_SOURCE_DIR}/App/Controller/Manager/Inc
    ${PROJECT_SOURCE_DIR}/App/Controller/Modules/Inc
    ${PROJECT_SOURCE_DIR}/App/Controller/Common
    ${PROJECT_SOURCE_DIR}/App/Controller/Interface  
    
    #블루투스 경로
    ${PROJECT_SOURCE_DIR}/Drivers/Ble/Inc
    
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
