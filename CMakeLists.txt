cmake_minimum_required(VERSION 3.10)

include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.20.57.tar.gz"
        SHA1 "4f4608e1c11b67df417bfc5a68d4b5a86251b852"
)

project(bullshit_generator)

set(CMAKE_CXX_STANDARD 17)

hunter_add_package(Boost COMPONENTS program_options)
find_package(Boost CONFIG REQUIRED program_options)

add_executable(bullshit_generator main.cpp BullshitGenerator.cpp)
target_link_libraries(${PROJECT_NAME} Boost::program_options)