## CsWebApp

### Introduction

CsWebApp is derivative work based on a library develeoped by Stefan Frings.

CsWebApp is an HTTP server library written in C++ which was inspired by Java Servlets. This library can be used
on versions of Linux, Windows and Mac OS which are supported by the CopperSpice libraries.

QtWebApp contains the following components:

* HTTP(S) 1.0 and 1.1 server
* Template engine
* Buffered file logger

The logger improves disk space and performance by retaining debug messages in memory until an error occurs. No debug
messages are written as long as everything works fine. Changes to the configuration of the logger become active
automatically without program restart.


### Usage

The following is a short example which shows how to use the CsWebApp library.

```C++
// The request handler receives and responds HTTP requests
void MyRequestHandler::service(HttpRequest &request, HttpResponse &response)
{
    // Get a request parameters
    QByteArray username = request.getParameter("username");

    // Set a response header
    response.setHeader("Content-Type", "text/html; charset=UTF-8");

    // Generate the HTML document
    response.write("<html><body>");
    response.write("Hello ");
    response.write(username);
    response.write("</body></html>");
}

// The main program starts the HTTP server
int main(int argc, char *argv[])
{
   QCoreApplication app(argc, argv);

   new HttpListener(
      new QSettings("configfile.ini", QSettings::IniFormat, &app),
      new MyRequestHandler(&app),
      &app
   );

    return app.exec();
}
```

### Building

To build CsWebApp from source a current copy of the CopperSpice libraries, a C++17 compiler, and a C++17 standard
library are required.

CMake build files are provided with the CsWebApp source distribution located on github.


### License

This program is released under the LGPL 3.0 license. For more information refer to the LICENSE file provided with
this project.


### References

* Website:  https://www.copperspice.com
* Twitter:  https://twitter.com/copperspice_cpp
* Email:    info@copperspice.com

* Github:   https://github.com/copperspice

* Forum:    https://forum.copperspice.com
* Journal:  https://journal.copperspice.com

