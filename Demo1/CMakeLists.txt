
CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

PROJECT(QtWebAppDemo1)

find_package(CopperSpice REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_VERBOSE_MAKEFILE 1)

add_definitions("/wd4127")
add_definitions("-DQT_NO_EMIT")
add_definitions("-DQT_NO_WEBKIT")

SET(QtWebAppDemo1_SOURCES
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

SET(QtWebAppDemo1_HEADERS
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

ADD_EXECUTABLE(${PROJECT_NAME}
    ${QtWebAppDemo1_SOURCES}
    ${QtWebAppDemo1_HEADERS}
)

target_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../QtWebApp
  ${CMAKE_CURRENT_SOURCE_DIR}/../QtWebApp/httpserver
  ${CMAKE_CURRENT_SOURCE_DIR}/../QtWebApp/logging
  ${CMAKE_CURRENT_SOURCE_DIR}/../QtWebApp/templateengine
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/controller
  D:/CS_1_8_2_MSVC_Install/include/
  D:/CS_1_8_2_MSVC_Install/include/QtCore
  D:/CS_1_8_2_MSVC_Install/include/QtNetwork
  D:/CS_1_8_2_MSVC_Install/include/QtSql
  D:/CS_1_8_2_MSVC_Install/include/QtGui
  )
  
target_LINK_DIRECTORIES(${PROJECT_NAME} PUBLIC
  ${CMAKE_BINARY_DIR}/QtWebAppCS
  )

target_link_libraries(${PROJECT_NAME} PUBLIC
   CopperSpice::CsCore
   CopperSpice::CsGui
   CopperSpice::CsNetwork
   CopperSpice::CsOpenGL
   CopperSpice::CsScript
   CopperSpice::CsSql
   CopperSpice::CsSvg
   CopperSpice::CsXml
   CopperSpice::CsXmlPatterns
   QtWebAppLibCS
)

# installs the CopperSpice libraries
cs_copy_library(CsCore)
cs_copy_library(CsGui)
cs_copy_library(CsNetwork)
cs_copy_library(CsOpenGL)
cs_copy_library(CsScript)
cs_copy_library(CsSql)
cs_copy_library(CsSvg)
cs_copy_library(CsXml)
cs_copy_library(CsXmlPatterns)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")

   set(CPACK_DMG_VOLUME_NAME QtWebAppDemo1)
   set(CPACK_DMG_FORMAT UDBZ)

   # installs the platform Gui plugin
   cs_copy_plugins(CsGui ../plugins)

   # two files
   if("Multimedia" IN_LIST COPPERSPICE_COMPONENTS)
      cs_copy_plugins(CsMultimedia ../plugins)
   endif()

elseif(CMAKE_SYSTEM_NAME MATCHES "(Linux|OpenBSD|FreeBSD|NetBSD|DragonFly)")

   # installs the platform Gui plugin
   cs_copy_plugins(CsGui)
   cs_copy_plugins(CsOpenGL)

   # three files
   if("Multimedia" IN_LIST COPPERSPICE_COMPONENTS)
      cs_copy_plugins(CsMultimedia)
   endif()

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
   cs_copy_plugins(CsGui)
elseif(CMAKE_SYSTEM_NAME MATCHES "MSVC")
  cs_copy_plugins(CsGui)
endif()

FILE(GLOB qtDllFiles ABSOLUTE "${CsRootPath}/bin/*.dll")

FOREACH(dllFname ${qtDllFiles})
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD        # Adds a post-build event to MyTest
                       COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
                       ${dllFname}      # <--this is in-file
                       $<TARGET_FILE_DIR:${PROJECT_NAME}>) 
ENDFOREACH(dllFname)