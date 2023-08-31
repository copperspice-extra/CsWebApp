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

#include <QCoreApplication>

#include "global.h"
#include "requestmapper.h"
#include "filelogger.h"
#include "staticfilecontroller.h"
#include "controller/dumpcontroller.h"
#include "controller/templatecontroller.h"
#include "controller/formcontroller.h"
#include "controller/fileuploadcontroller.h"
#include "controller/sessioncontroller.h"
#include "controller/logincontroller.h"

RequestMapper::RequestMapper(QObject* parent)
    :HttpRequestHandler(parent)
{
    qDebug("RequestMapper: created");
}


RequestMapper::~RequestMapper()
{
    qDebug("RequestMapper: deleted");
}


void RequestMapper::service(HttpRequest& request, HttpResponse& response)
{
    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());

    // For the following pathes, each request gets its own new instance of the related controller.

    if (path.startsWith("/dump"))
    {
        DumpController().service(request, response);
    }

    else if (path.startsWith("/template"))
    {
        TemplateController().service(request, response);
    }

    else if (path.startsWith("/form"))
    {
        FormController().service(request, response);
    }

    else if (path.startsWith("/file"))
    {
        FileUploadController().service(request, response);
    }

    else if (path.startsWith("/session"))
    {
        SessionController().service(request, response);
    }

    else if (path.startsWith("/login"))
    {
        LoginController().service(request, response);
    }

    // All other pathes are mapped to the static file controller.
    // In this case, a single instance is used for multiple requests.
    else
    {
        staticFileController->service(request, response);
    }

    qDebug("RequestMapper: finished request");

    // Clear the log buffer
    if (logger)
    {
       logger->clear();
    }
}
