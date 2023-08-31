CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

PROJECT(CsWebAppDemo1)

find_package(CopperSpice REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (MSVC)
   add_definitions("/wd4127")
endif()

add_definitions("-DQT_NO_EMIT")

set(CsWebAppDemo1_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/global.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/requestmapper.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/dumpcontroller.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/fileuploadcontroller.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/formcontroller.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/logincontroller.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/sessioncontroller.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/templatecontroller.cpp
)

set(CsWebAppDemo1_HEADERS
   ${CMAKE_CURRENT_SOURCE_DIR}/src/documentcache.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/global.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/requestmapper.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/dumpcontroller.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/fileuploadcontroller.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/formcontroller.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/logincontroller.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/sessioncontroller.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/templatecontroller.h
)

add_executable(CsWebAppDemo1
   ${CsWebAppDemo1_SOURCES}
   ${CsWebAppDemo1_HEADERS}
)

target_include_directories(CsWebAppDemo1
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/src
   ${CMAKE_CURRENT_SOURCE_DIR}/src/controller
)

target_link_libraries(CsWebAppDemo1
   PUBLIC
   CopperSpice::CsCore
   CopperSpice::CsNetwork
   CsWebAppLib
)

install(TARGETS CsWebAppDemo1 DESTINATION .)

# installs the CopperSpice libraries
cs_copy_library(CsCore)
cs_copy_library(CsNetwork)

