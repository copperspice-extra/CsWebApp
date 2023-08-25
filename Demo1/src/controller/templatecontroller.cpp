/**
  @file
  @author Stefan Frings
*/

#include "../global.h"
#include "templatecontroller.h"
#include "templatecache.h"
#include "template.h"

TemplateController::TemplateController()
{}

void TemplateController::service(HttpRequest& request, HttpResponse& response)
{
    response.setHeader("Content-Type", "text/html; charset=UTF-8");

    Template t=templateCache->getTemplate("demo",request.getHeader("Accept-Language"));
    t.enableWarnings();
    t.setVariable("path",request.getPath());

    QMultiMap<QByteArray,QByteArray> headers=request.getHeaderMap();
    QMultiMapIterator<QByteArray,QByteArray> iterator(headers);

    t.loop("header",headers.size());
    int i=0;
    while (iterator.hasNext())
    {
        iterator.next();
        t.setVariable(QString("header%1.name").formatArg(i),QString(iterator.key()));
        t.setVariable(QString("header%1.value").formatArg(i),QString(iterator.value()));
        ++i;
    }

    response.write(t.toUtf8(),true);
}
