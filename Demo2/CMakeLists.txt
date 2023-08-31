CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

PROJECT(CsWebAppDemo2)

find_package(CopperSpice REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (MSVC)
   add_definitions("/wd4127")
endif()

add_definitions("-DQT_NO_EMIT")

set(CsWebAppDemo2_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/requesthandler.cpp
)

set(CsWebAppDemo2_HEADERS
   ${CMAKE_CURRENT_SOURCE_DIR}/src/requesthandler.h
)

add_executable(CsWebAppDemo2
   ${CsWebAppDemo2_SOURCES}
   ${CsWebAppDemo2_HEADERS}
)

target_include_directories(CsWebAppDemo2
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(CsWebAppDemo2
   PUBLIC
   CopperSpice::CsCore
   CopperSpice::CsNetwork
   CsWebAppLib
)

install(TARGETS CsWebAppDemo2 DESTINATION .)

# installs the CopperSpice libraries
cs_copy_library(CsCore)
cs_copy_library(CsNetwork)
