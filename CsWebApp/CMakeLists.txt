CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

PROJECT(CsWebAppLib)

if (MSVC)
   include("${CMAKE_SOURCE_DIR}/WindowsFlags.cmake")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckTypeSize)

find_package(CopperSpice REQUIRED)

if (MSVC)
   add_definitions("/wd4127")
   add_definitions("-D_CRT_SECURE_NO_WARNINGS")
   add_definitions(-DUNICODE -D_UNICODE)
endif()

set(CsWebAppLib_SOURCES
  httpserver/httpconnectionhandler.cpp
  httpserver/httpconnectionhandlerpool.cpp
  httpserver/httpcookie.cpp
  httpserver/httpglobal.cpp
  httpserver/httplistener.cpp
  httpserver/httprequest.cpp
  httpserver/httprequesthandler.cpp
  httpserver/httpresponse.cpp
  httpserver/httpsession.cpp
  httpserver/httpsessionstore.cpp
  httpserver/staticfilecontroller.cpp

  logging/dualfilelogger.cpp
  logging/filelogger.cpp
  logging/logger.cpp
  logging/logmessage.cpp

  templateengine/template.cpp
  templateengine/templatecache.cpp
  templateengine/templateloader.cpp
)

set(CsWebAppLib_HEADERS
  httpserver/httpconnectionhandler.h
  httpserver/httpconnectionhandlerpool.h
  httpserver/httpcookie.h
  httpserver/httpglobal.h
  httpserver/httplistener.h
  httpserver/httprequest.h
  httpserver/httprequesthandler.h
  httpserver/httpresponse.h
  httpserver/httpsession.h
  httpserver/httpsessionstore.h
  httpserver/staticfilecontroller.h

  logging/dualfilelogger.h
  logging/filelogger.h
  logging/logger.h
  logging/logmessage.h
  logging/logglobal.h

  templateengine/template.h
  templateengine/templatecache.h
  templateengine/templateglobal.h
  templateengine/templateloader.h
)

add_library(CsWebAppLib
   SHARED
   ${CsWebAppLib_SOURCES}
   ${CsWebAppLib_HEADERS}
)

target_include_directories(CsWebAppLib
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>

  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/httpserver>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/logging>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/qtservice>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/templateengine>

  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/httpserver>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/logging>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/qtservice>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/templateengine>
)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
   # msvc and mingw

   target_compile_definitions(CsWebAppLib
      PRIVATE
      -DQTWEBAPPLIB_EXPORT
   )

   target_compile_definitions(CsWebAppLib
      INTERFACE
      -DQTWEBAPPLIB_IMPORT
   )
endif()

# Enable very detailed debug messages when compiling the debug version
if (CMAKE_BUILD_TYPE MATCHES "Debug")
   target_compile_definitions(CsWebAppLib
      PRIVATE
      -DSUPERVERBOSE
   )
endif()

install(TARGETS CsWebAppLib DESTINATION .)

target_link_libraries(CsWebAppLib
   PUBLIC
   CopperSpice::CsCore
   CopperSpice::CsNetwork
)
