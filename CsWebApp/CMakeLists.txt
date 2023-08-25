

CMAKE_MINIMUM_REQUIRED(VERSION 3.23)

PROJECT(QtWebAppLibCS)

include("${CMAKE_SOURCE_DIR}/WindowsFlags.cmake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_VERBOSE_MAKEFILE 1)

include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckTypeSize)

#set(CMAKE_PREFIX_PATH "${CsRootPath}/cmake/CopperSpice")
find_package(CopperSpice REQUIRED)

add_definitions("/wd4127")
add_definitions(-DUNICODE -D_UNICODE)
add_definitions("-DQT_SSL")
add_definitions("-D_CRT_SECURE_NO_WARNINGS")
add_definitions("-DQT_NO_KEYWORDS")
add_definitions("-DQT_NO_WEBKIT")

INCLUDE_DIRECTORIES(
  D:/CS_1_8_2_MSVC_Install/include
  D:/CS_1_8_2_MSVC_Install/include/QtCore
  D:/CS_1_8_2_MSVC_Install/include/QtNetwork
  D:/CS_1_8_2_MSVC_Install/include/QtSql
  D:/CS_1_8_2_MSVC_Install/include/QtGui
  ${CMAKE_SOURCE_DIR}/httpserver
  ${CMAKE_SOURCE_DIR}/logging
  ${CMAKE_SOURCE_DIR}/qtservice
  ${CMAKE_SOURCE_DIR}/templateengine
  )

SET(QtWebAppLibCS_SOURCES
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
  #qtservice/qtservice.cpp
  #qtservice/qtunixserversocket.cpp
  #qtservice/qtunixsocket.cpp
  #qtservice/qtservice_unix.cpp
  #qtservice/qtservice_win.cpp
  templateengine/template.cpp
  templateengine/templatecache.cpp
  templateengine/templateloader.cpp
)

SET(QtWebAppLibCS_HEADERS
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
  #qtservice/qtservice_p.h
  #qtservice/qtservice.h
  #qtservice/qtunixserversocket.h
  #qtservice/qtunixsocket.h
  templateengine/template.h
  templateengine/templatecache.h
  templateengine/templateglobal.h
  templateengine/templateloader.h
)

ADD_LIBRARY(${CMAKE_PROJECT_NAME}
    ${QtWebAppLibCS_SOURCES}
    ${QtWebAppLibCS_HEADERS}
)

target_link_libraries(${CMAKE_PROJECT_NAME}
                      CopperSpice::CsCore
                      CopperSpice::CsGui
                      CopperSpice::CsNetwork
                      CopperSpice::CsSql)

