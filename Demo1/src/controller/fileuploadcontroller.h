/**
  @file
  @author Stefan Frings
*/

#ifndef FILEUPLOADCONTROLLER_H
#define FILEUPLOADCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

using namespace stefanfrings;

/**
  This controller displays a HTML form for file upload and recieved the file.
*/


class FileUploadController : public HttpRequestHandler {
    CS_OBJECT(FileUploadController)
    Q_DISABLE_COPY(FileUploadController)
public:

    /** Constructor */
    FileUploadController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // FILEUPLOADCONTROLLER_H
