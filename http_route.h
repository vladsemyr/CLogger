#ifndef HTTP_ROUTE_H
#define HTTP_ROUTE_H

#include "http_header_parser.h"

typedef int (*HttpRouteFunction)();

struct HttpRouteTableRow {
    enum HttpMethod method;
    String_t url;
    HttpRouteFunction function;
};

struct HttpRouteTable {
    struct HttpRouteTableRow *rows;
    size_t row_registered_count;
};

// TODO: функция инициализации таблицы

void HttpRouteRegisterUrl(
    struct HttpRouteTable *table,
    enum HttpMethod method,
    String_t *url,
    HttpRouteFunction function);

#define HttpRouteRegisterUrl2(ptr_table, method, url, function) {   \
        String_t _url = stringMethods.Create(url, sizeof(url)-1);   \
        HttpRouteRegisterUrl(                                       \
            ptr_table,                                              \
            method,                                                 \
            &_url,                                                  \
            function                                                \
        );                                                          \
    }

void HttpRoute(
    struct HttpRouteTable *route_table,
    struct HttpRequest *request);

#endif