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

#ifndef TEMPLATECONTROLLER_H
#define TEMPLATECONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

using namespace stefanfrings;

/**
  This controller generates a website using the template engine.
*/

class TemplateController : public HttpRequestHandler {
    CS_OBJECT(TemplateController)
    Q_DISABLE_COPY(TemplateController)
public:

    /** Constructor */
    TemplateController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // TEMPLATECONTROLLER_H
