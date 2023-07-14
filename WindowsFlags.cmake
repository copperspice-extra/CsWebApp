

SET(SCC_MAKE_LINKER_FLAGS_DEBUG "/DEBUG /INCREMENTAL /NODEFAULTLIB:VCOMPD")
SET(SCC_MAKE_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO /NODEFAULTLIB:VCOMP")
SET(SCC_MAKE_LINKER_FLAGS_RELWITHDEBINFO "/DEBUG ${SCC_MAKE_LINKER_FLAGS_RELEASE}")
SET(SCC_MAKE_LINKER_FLAGS_MINSIZEREL "${SCC_MAKE_LINKER_FLAGS_RELEASE}")

SET(SCC_MAKE_FLAGS_DEBUG "/Od /Zi")
SET(SCC_MAKE_FLAGS_RELEASE "/Ox")
SET(SCC_MAKE_FLAGS_RELWITHDEBINFO "/Zi /O2")
SET(SCC_MAKE_FLAGS_MINSIZEREL "/O1")

SET(SCC_MAKE_C_FLAGS "/nologo /W4")
SET(SCC_MAKE_C_FLAGS_DEBUG "")
SET(SCC_MAKE_C_FLAGS_RELEASE "")
SET(SCC_MAKE_C_FLAGS_RELWITHDEBINFO "/Ob1")
SET(SCC_MAKE_C_FLAGS_MINSIZEREL "/Ob1")

SET(SCC_MAKE_CXX_FLAGS "${SCC_MAKE_C_FLAGS} /EHsc /wd4127 /wd4512 /wd4996")
SET(SCC_MAKE_CXX_FLAGS_DEBUG "")
SET(SCC_MAKE_CXX_FLAGS_RELEASE "")
SET(SCC_MAKE_CXX_FLAGS_RELWITHDEBINFO "/Ob1")
SET(SCC_MAKE_CXX_FLAGS_MINSIZEREL "/Ob1")

SET(SCC_MAKE_FORTRAN_FLAGS "/nologo /warn:truncated_source,uncalled,unused /assume:byterecl,underscore /names:lowercase /auto /extend-source")
SET(SCC_MAKE_FORTRAN_FLAGS_DEBUG "/check:all /Qtrapuv")
SET(SCC_MAKE_FORTRAN_FLAGS_RELEASE "")
SET(SCC_MAKE_FORTRAN_FLAGS_RELWITHDEBINFO "/debug:full ${SCC_MAKE_FORTRAN_FLAGS_DEBUG}")
SET(SCC_MAKE_FORTRAN_FLAGS_MINSIZEREL "${SCC_MAKE_FORTRAN_FLAGS_RELEASE}")

SET(SCC_MAKE_DEFINITIONS "/DWIN32 /D_WINDOWS /DNOMINMAX /D_USE_MATH_DEFINES /D_CRT_SECURE_NO_DEPRECATE /D_CRT_SECURE_NO_WARNINGS")
SET(SCC_MAKE_DEFINITIONS_DEBUG "/D_DEBUG /D_SECURE_SCL=1")
SET(SCC_MAKE_DEFINITIONS_RELEASE "/DNDEBUG /D_SECURE_SCL=0")
SET(SCC_MAKE_DEFINITIONS_RELWITHDEBINFO "${SCC_MAKE_DEFINITIONS_RELEASE}")
SET(SCC_MAKE_DEFINITIONS_MINSIZEREL "${SCC_MAKE_DEFINITIONS_RELEASE}")

SET(SCC_MAKE_CODE_GENERATION_FLAGS "/MP")
#IF (SCC_MAKE_MODE_STATIC OR SCC_MAKE_MODE_DLM)
#  SET(SCC_MAKE_CODE_GENERATION_FLAGS_DEBUG "/MTd")
#  SET(SCC_MAKE_CODE_GENERATION_FLAGS_RELEASE "/MT")
#ELSE()
  SET(SCC_MAKE_CODE_GENERATION_FLAGS_DEBUG "/MDd")
  SET(SCC_MAKE_CODE_GENERATION_FLAGS_RELEASE "/MD")
#ENDIF()

#
# Enable required languages
#

ENABLE_LANGUAGE(C)
ENABLE_LANGUAGE(CXX)
#ENABLE_LANGUAGE(Fortran)

  SET(CMAKE_C_FLAGS "${SCC_MAKE_C_FLAGS} ${SCC_MAKE_CODE_GENERATION_FLAGS} ${SCC_MAKE_DEFINITIONS}" CACHE STRING "SCC-Make: C compiler flags" FORCE)
  
  SET(CMAKE_CXX_FLAGS "${SCC_MAKE_CXX_FLAGS} ${SCC_MAKE_CODE_GENERATION_FLAGS} ${SCC_MAKE_DEFINITIONS}" CACHE STRING "SCC-Make: C++ compiler flags" FORCE)
  
  SET(CMAKE_Fortran_FLAGS "${SCC_MAKE_FORTRAN_FLAGS} ${SCC_MAKE_CODE_GENERATION_FLAGS}" CACHE STRING "SCC-Make: Fortran compiler flags" FORCE)
  
  SET(CMAKE_C_FLAGS_DEBUG "${SCC_MAKE_FLAGS_DEBUG} ${SCC_MAKE_C_FLAGS_DEBUG} ${SCC_MAKE_CODE_GENERATION_FLAGS_DEBUG} ${SCC_MAKE_DEFINITIONS_DEBUG}" CACHE STRING "SCC-Make: Debug mode C compiler flags" FORCE)
  
  SET(CMAKE_CXX_FLAGS_DEBUG "${SCC_MAKE_FLAGS_DEBUG} ${SCC_MAKE_CXX_FLAGS_DEBUG} ${SCC_MAKE_CODE_GENERATION_FLAGS_DEBUG} ${SCC_MAKE_DEFINITIONS_DEBUG}" CACHE STRING "SCC-Make: Debug mode C++ compiler flags" FORCE)
  
  SET(CMAKE_Fortran_FLAGS_DEBUG "${SCC_MAKE_FLAGS_DEBUG} ${SCC_MAKE_FORTRAN_FLAGS_DEBUG} ${SCC_MAKE_CODE_GENERATION_FLAGS_DEBUG}" CACHE STRING "SCC-Make: Debug mode Fortran compiler flags" FORCE)
  
  SET(CMAKE_C_FLAGS_RELEASE "${SCC_MAKE_FLAGS_RELEASE} ${SCC_MAKE_C_FLAGS_RELEASE} ${SCC_MAKE_CODE_GENERATION_FLAGS_RELEASE} ${SCC_MAKE_DEFINITIONS_RELEASE}" CACHE STRING "SCC-Make: Release mode C compiler flags" FORCE)
  
  SET(CMAKE_CXX_FLAGS_RELEASE "${SCC_MAKE_FLAGS_RELEASE} ${SCC_MAKE_CXX_FLAGS_RELEASE} ${SCC_MAKE_CODE_GENERATION_FLAGS_RELEASE} ${SCC_MAKE_DEFINITIONS_RELEASE}" CACHE STRING "SCC-Make: Release mode C++ compiler flags" FORCE)
  
  SET(CMAKE_Fortran_FLAGS_RELEASE "${SCC_MAKE_FLAGS_RELEASE} ${SCC_MAKE_FORTRAN_FLAGS_RELEASE} ${SCC_MAKE_CODE_GENERATION_FLAGS_RELEASE}" CACHE STRING "SCC-Make: Release mode Fortran compiler flags" FORCE)
  
  SET(CMAKE_C_FLAGS_RELWITHDEBINFO "${SCC_MAKE_FLAGS_RELWITHDEBINFO} ${SCC_MAKE_C_FLAGS_RELWITHDEBINFO} ${SCC_MAKE_CODE_GENERATION_FLAGS_RELWITHDEBINFO} ${SCC_MAKE_DEFINITIONS_RELWITHDEBINFO}" CACHE STRING "SCC-Make: Release debuggable mode C compiler flags" FORCE)
  
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${SCC_MAKE_FLAGS_RELWITHDEBINFO} ${SCC_MAKE_CXX_FLAGS_RELWITHDEBINFO} ${SCC_MAKE_CODE_GENERATION_FLAGS_RELWITHDEBINFO} ${SCC_MAKE_DEFINITIONS_RELWITHDEBINFO}" CACHE STRING "SCC-Make: Release debuggable mode C++ compiler flags" FORCE)
  
  SET(CMAKE_Fortran_FLAGS_RELWITHDEBINFO "${SCC_MAKE_FLAGS_RELWITHDEBINFO} ${SCC_MAKE_FORTRAN_FLAGS_RELWITHDEBINFO} ${SCC_MAKE_CODE_GENERATION_FLAGS_RELWITHDEBINFO}" CACHE STRING "SCC-Make: Release debuggable mode Fortran compiler flags" FORCE)
  
  SET(CMAKE_C_FLAGS_MINSIZEREL "${SCC_MAKE_FLAGS_MINSIZEREL} ${SCC_MAKE_C_FLAGS_MINSIZEREL} ${SCC_MAKE_CODE_GENERATION_FLAGS_MINSIZEREL} ${SCC_MAKE_DEFINITIONS_MINSIZEREL}" CACHE STRING "SCC-Make: Release stripped mode C compiler flags" FORCE)
  
  SET(CMAKE_CXX_FLAGS_MINSIZEREL "${SCC_MAKE_FLAGS_MINSIZEREL} ${SCC_MAKE_CXX_FLAGS_MINSIZEREL} ${SCC_MAKE_CODE_GENERATION_FLAGS_MINSIZEREL} ${SCC_MAKE_DEFINITIONS_MINSIZEREL}" CACHE STRING "SCC-Make: Release stripped mode C++ compiler flags" FORCE)
  
  SET(CMAKE_Fortran_FLAGS_MINSIZEREL "${SCC_MAKE_FLAGS_MINSIZEREL} ${SCC_MAKE_FORTRAN_FLAGS_MINSIZEREL} ${SCC_MAKE_CODE_GENERATION_FLAGS_MINSIZEREL}" CACHE STRING "SCC-Make: Release stripped mode Fortran compiler flags" FORCE)
  
  SET(CMAKE_EXE_LINKER_FLAGS "${SCC_MAKE_LINKER_FLAGS}" CACHE STRING "SCC-Make: Executable linker flags" FORCE)
  
  SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${SCC_MAKE_LINKER_FLAGS_DEBUG}" CACHE STRING "SCC-Make: Debug mode executable linker flags" FORCE)
  
  SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${SCC_MAKE_LINKER_FLAGS_RELEASE}" CACHE STRING "SCC-Make: Release mode executable linker flags" FORCE)
  
  SET(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${SCC_MAKE_LINKER_FLAGS_RELWITHDEBINFO}" CACHE STRING "SCC-Make: Release debuggable mode executable linker flags" FORCE)

  SET(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "${SCC_MAKE_LINKER_FLAGS_MINSIZEREL}" CACHE STRING "SCC-Make: Release stripped mode executable linker flags" FORCE)

  SET(CMAKE_MODULE_LINKER_FLAGS "${SCC_MAKE_LINKER_FLAGS}" CACHE STRING "SCC-Make: Module linker flags" FORCE)
  
  SET(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${SCC_MAKE_LINKER_FLAGS_DEBUG}" CACHE STRING "SCC-Make: Debug mode module linker flags" FORCE)
  
  SET(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${SCC_MAKE_LINKER_FLAGS_RELEASE}" CACHE STRING "SCC-Make: Release mode module linker flags" FORCE)
  
  SET(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO "${SCC_MAKE_LINKER_FLAGS_RELWITHDEBINFO}" CACHE STRING "SCC-Make: Release debuggable mode module linker flags" FORCE)

  SET(CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL "${SCC_MAKE_LINKER_FLAGS_MINSIZEREL}" CACHE STRING "SCC-Make: Release stripped mode module linker flags" FORCE)

  SET(CMAKE_SHARED_LINKER_FLAGS "${SCC_MAKE_LINKER_FLAGS}" CACHE STRING "SCC-Make: Shared library linker flags" FORCE)
  
  SET(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${SCC_MAKE_LINKER_FLAGS_DEBUG}" CACHE STRING "SCC-Make: Debug mode shared library linker flags" FORCE)
  
  SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${SCC_MAKE_LINKER_FLAGS_RELEASE}" CACHE STRING "SCC-Make: Release mode shared library linker flags" FORCE)

  SET(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "${SCC_MAKE_LINKER_FLAGS_RELWITHDEBINFO}" CACHE STRING "SCC-Make: Release debuggable mode shared library linker flags" FORCE)
  
  SET(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "${SCC_MAKE_LINKER_FLAGS_MINSIZEREL}" CACHE STRING "SCC-Make: Release stripped mode shared library linker flags" FORCE)
  
  SET(CMAKE_INSTALL_PREFIX "${SCC_MAKE_INSTALL_PREFIX}" CACHE STRING "SCC-Make: Installation directory" FORCE)

  SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH 1 CACHE INTERNAL "SCC-Make: Retain default linker search path in installed targets" FORCE)

  SET(SCC_MAKE_CACHE_INITIALIZED ${SCC_MAKE_VERSION} CACHE INTERNAL "SCC-Make: Internal cache version" FORCE)
