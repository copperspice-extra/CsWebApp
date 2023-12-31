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

#include "fileuploadcontroller.h"

FileUploadController::FileUploadController()
{}

void FileUploadController::service(HttpRequest& request, HttpResponse& response)
{

    if (request.getParameter("action")=="show")
    {
        response.setHeader("Content-Type", "image/jpeg");
        QTemporaryFile* file=request.getUploadedFile("file1");
        if (file)
        {
            while (!file->atEnd() && !file->error())
            {
                QByteArray buffer=file->read(65536);
                response.write(buffer);
            }
        }
        else
        {
            response.write("upload failed");
        }
    }

    else
    {
        response.setHeader("Content-Type", "text/html; charset=UTF-8");
        response.write("<html><body>");
        response.write("Upload a JPEG image file<p>");
        response.write("<form method=\"post\" enctype=\"multipart/form-data\">");
        response.write("  <input type=\"hidden\" name=\"action\" value=\"show\">");
        response.write("  File: <input type=\"file\" name=\"file1\"><br>");
        response.write("  <input type=\"submit\">");
        response.write("</form>");
        response.write("</body></html>",true);
    }
}

