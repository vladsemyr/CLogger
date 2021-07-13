#include "http_route.h"
#include <stdbool.h>
#include <memory.h>

void HttpRouteRegisterUrl(
    struct HttpRouteTable *table,
    enum HttpMethod method,
    String_t *url,
    HttpRouteFunction function
) {
    table->rows[table->row_registered_count].method = method;
    table->rows[table->row_registered_count].url = stringMethods.SimpleClone(url);
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
        
        bool is_url_equal = stringMethods.Compare(&request->path, &route_table->rows[i].url);
        if (!is_url_equal)
            continue;
        
        route_table->rows[i].function();
    }
}