cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(riscv_emu LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp src/cpu.cpp src/instruction_execute.cpp src/utils.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE src/cpu.hpp src/utils.hpp)

# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)

# find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
# qt_standard_project_setup()

# qt_add_executable(${PROJECT_NAME} src/main.cpp src/cpu.cpp src/instruction_execute.cpp src/utils.cpp)

# target_link_libraries(${PROJECT_NAME} PRIVATE 
#     Qt6::Widgets
#     Qt6::Core
# )
