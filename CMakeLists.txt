cmake_minimum_required(VERSION 3.20)
project(DLMSAPDUParser C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(parser/src)

add_executable(DLMSAPDUParser main.c)

target_link_libraries(DLMSAPDUParser DLMSAPDUParserDyLib)
target_link_libraries(DLMSAPDUParser m)