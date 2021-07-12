#include "http_route.h"
#include <stdbool.h>
#include <memory.h>

void HttpRouteRegisterUrl(
    struct HttpRouteTable *table,
    enum HttpMethod method,
    struct HttpString *url,
    HttpRouteFunction function
) {
    table->rows[table->row_registered_count].method = method;
    table->rows[table->row_registered_count].url.ptr = url->ptr;
    table->rows[table->row_registered_count].url.len = url->len;
    table->rows[table->row_registered_count].function = function;
    table->row_registered_count += 1;
}


void HttpRoute(
    struct HttpRouteTable *route_table,
    struct HttpRequest *request
) {
    for (size_t i = 0; i < route_table->row_registered_count; ++i) {
        bool is_method_equal = route_table->rows[i].method == request->method;
        if (!is_method_equal)
            continue;
        
        // TODO: отдельный файл с HttpString и его функциями
        if (request->path.len != route_table->rows[i].url.len)
            continue;
        
        bool is_url_equal = strncmp(
            route_table->rows[i].url.ptr,
            request->path.ptr,
            route_table->rows[i].url.len
        );
        
        if (is_url_equal != 0)
            continue;
        
        route_table->rows[i].function();
    }
}