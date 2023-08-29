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

#ifndef SESSIONCONTROLLER_H
#define SESSIONCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

using namespace stefanfrings;

/**
  This controller demonstrates how to use sessions.
*/

class SessionController : public HttpRequestHandler {
    CS_OBJECT(SessionController)
    Q_DISABLE_COPY(SessionController)
public:

    /** Constructor */
    SessionController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // SESSIONCONTROLLER_H
