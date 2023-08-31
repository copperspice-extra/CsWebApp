/**
  @file
  @author Stefan Frings
*/

/**************************************************************************
*
* Copyright 2023 Barbara Geller
* Copyright 2023 Ansel Sermersheim
*
* CsWebApp is released under the LGPL 3.0 license and is derivative work
*
* This project is distributed WITHOUT ANY WARRANTY; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
**************************************************************************/

#ifndef LOGGLOBAL_H
#define LOGGLOBAL_H

#include <QGlobal>

// This is specific to Windows dll's
#if defined(Q_OS_WIN)
#   if defined(QTWEBAPPLIB_EXPORT)
#      define DECLSPEC Q_DECL_EXPORT
#   elif defined(QTWEBAPPLIB_IMPORT)
#      define DECLSPEC Q_DECL_IMPORT
#   endif
#endif

#if ! defined(DECLSPEC)
#   define DECLSPEC
#endif

#endif // LOGGLOBAL_H

