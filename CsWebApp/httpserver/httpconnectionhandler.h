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

#ifndef HTTPCONNECTIONHANDLER_H
#define HTTPCONNECTIONHANDLER_H

#if defined (QT_SSL)
#   include <QSslConfiguration>
#endif

#include <QSettings>
#include <QTcpSocket>
#include <QThread>
#include <QTimer>

#include "httpglobal.h"
#include "httprequest.h"
#include "httprequesthandler.h"

namespace stefanfrings {

/** Alias type definition, for compatibility to different Qt versions */

typedef qintptr tSocketDescriptor;

/** Alias for QSslConfiguration if OpenSSL is not supported */
#if ! defined (QT_SSL)
#   define QSslConfiguration QObject
#endif

/**
  The connection handler accepts incoming connections and dispatches incoming requests to to a
  request mapper. Since HTTP clients can send multiple requests before waiting for the response,
  the incoming requests are queued and processed one after the other.
  <p>
  Example for the required configuration settings:
  <code><pre>
  readTimeout=60000
  maxRequestSize=16000
  maxMultiPartSize=1000000
  </pre></code>
  <p>
  The readTimeout value defines the maximum time to wait for a complete HTTP request.
  <p>
  MaxRequestSize is the maximum size of a HTTP request. In case of
  multipart/form-data requests (also known as file-upload), the maximum
  size of the body must not exceed maxMultiPartSize.
*/
class DECLSPEC HttpConnectionHandler : public QObject {
    CS_OBJECT(HttpConnectionHandler)
    Q_DISABLE_COPY(HttpConnectionHandler)

public:

    /**
      Constructor.
      @param settings Configuration settings of the HTTP webserver
      @param requestHandler Handler that will process each incoming HTTP request
      @param sslConfiguration SSL (HTTPS) will be used if not NULL
    */
    HttpConnectionHandler(const QSettings* settings, HttpRequestHandler* requestHandler,
                          const QSslConfiguration* sslConfiguration=nullptr);

    /** Destructor */
    virtual ~HttpConnectionHandler();

    /** Returns true, if this handler is in use. */
    bool isBusy();

    /** Mark this handler as busy */
    void setBusy();

    /**
      Received from from the listener, when the handler shall start processing a new connection.
      @param socketDescriptor references the accepted connection.
    */
    CS_SLOT_1(Public, void handleConnection(const tSocketDescriptor socketDescriptor))
    CS_SLOT_2(handleConnection)

private:

    /** Configuration settings */
    const QSettings* settings;

    /** TCP socket of the current connection  */
    QTcpSocket* socket;

    /** The thread that processes events of this connection */
    QThread* thread;

    /** Time for read timeout detection */
    QTimer readTimer;

    /** Storage for the current incoming HTTP request */
    HttpRequest* currentRequest;

    /** Dispatches received requests to services */
    HttpRequestHandler* requestHandler;

    /** This shows the busy-state from a very early time */
    bool busy;

    /** Configuration for SSL */
    const QSslConfiguration* sslConfiguration;

    /**  Create SSL or TCP socket */
    void createSocket();

    /** Received from the socket when a read-timeout occured */
    CS_SLOT_1(Private, void readTimeout())
    CS_SLOT_2(readTimeout)

    /** Received from the socket when incoming data can be read */
    CS_SLOT_1(Private, void read())
    CS_SLOT_2(read)

    /** Received from the socket when a connection has been closed */
    CS_SLOT_1(Private, void disconnected())
    CS_SLOT_2(disconnected)

    /** Cleanup after the thread is closed */
    CS_SLOT_1(Private, void thread_done())
    CS_SLOT_2(thread_done)
};

} // end of namespace

#endif // HTTPCONNECTIONHANDLER_H
