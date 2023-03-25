CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
project(DLMSAPDUParserDyLib C)

set(CMAKE_C_STANDARD 11)

aux_source_directory(../../development/src GuruxDLMS)

aux_source_directory(. DIR_SRC)

add_library(DLMSAPDUParserDyLib SHARED ${GuruxDLMS} ${DIR_SRC})