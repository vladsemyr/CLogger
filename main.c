#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>

#include "log.h"
#include "http_header_parser.h"
#include "http_route.h"


char global_url_buffer[512];
String_t global_url = {
    .array_base = {
        .pointer = global_url_buffer,
        .count = 0
    }
};


struct HttpRouteTableRow http_route_table_rows[20];
struct HttpRouteTable http_route_table = {
    .rows = http_route_table_rows,
    .row_registered_count = 0
};

int f1() {
    consoleLogger.LPut(LOGGER_GREEN("F1"));
    return 0;
}

void RegisterUrl() {
    HttpRouteRegisterUrl2(
        &http_route_table,
        HTTP_METHOD_GET,
        "/main",
        f1
    );
}


int ReadFromClient(int fd) {
    char buffer[512];
    int nbytes;
    
    nbytes = read(fd, buffer, 512);
    if (nbytes < 0) {
        consoleLogger.LPut(LOGGER_FULL_ERR "read()");
        exit(1);
    }
    else if (nbytes == 0) {
        // EOF
        return -1;
    }
    else {
        consoleLogger.LPrintf(LOGGER_F "Msg: `" LOGGER_GRAY("%s") "`", buffer);
        
        // http parse
        struct HttpRequest request;
        enum HttpParseHeaderError parse_err = HttpHeaderParse(buffer, &request);
        if (parse_err != HTTP_PARSE_HEADER_OK) {
            consoleLogger.LPrintf(LOGGER_FULL_ERR "parse_err == %d", parse_err);
            return -1;
        }
        
        HttpRoute(&http_route_table, &request);
        
        strncpy(global_url_buffer, request.path.array_base.pointer, request.path.array_base.count);
        global_url.array_base.count = request.path.array_base.count;
        
        return 0;
    }
}


int WriteToClient(int fd) {
    int nbyte = write(fd, global_url.array_base.pointer, global_url.array_base.count);
    return nbyte > 0 ? 0 : -1;
}

#include "common/string/string.h"

int main() {
    String_t s1 = {
        .array_base = {
            .pointer = "NULL123456484654asfdfgjkmdf;kgj;sdflkgj;dslfgjldfgdf",
            .count = sizeof("NULL123456484654asfdfgjkmdf;kgj;sdflkgj;dslfgjldfgdf") - 1
        }
    };
    String_t s2 = {
        .array_base = {
            .pointer = "NULL123456484654asfdfgjkmdf;kgj;sdflkgj;dslfgjldfgdf",
            .count = sizeof("NULL123456484654asfdfgjkmdf;kgj;sdflkgj;dslfgjldfgdf") - 1
        }
    };
    
    consoleLogger.LPrintf(LOGGER_GREEN("%d"), stringMethods.Compare(&s1, &s2));
    //return 0;
    
    RegisterUrl();
    consoleLogger.LPrintf(LOGGER_GREEN("Compiled with GCC %s"), __VERSION__);
    
    int listen_fd;
    struct addrinfo hints, *res, *p;
    const char *port = "4030"; // TODO: заменить на константу
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo(NULL, port, &hints, &res) != 0) {
        consoleLogger.LPrintf(LOGGER_FULL_ERR "getaddrinfo()");
        exit(1);
    }
    
    for (p = res; p != NULL; p = p->ai_next) {
        int option = 1;
        listen_fd = socket(p->ai_family, p->ai_socktype, 0);
        setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
        if (listen_fd == -1) continue;
        if (bind(listen_fd, p->ai_addr, p->ai_addrlen) == 0) break;
    }
    
    if (p == NULL) {
        consoleLogger.LPut(LOGGER_FULL_ERR "socket() or bind()");
        exit(1);
    }
    
    freeaddrinfo(res);
    
    if (listen(listen_fd, 1000000) != 0) {
        consoleLogger.LPut(LOGGER_FULL_ERR "listen()");
        exit(1);
    }
    
    
    socklen_t size;
    fd_set active_fd_set, read_fd_set;
    struct sockaddr_in clientname;
    FD_ZERO(&active_fd_set);
    FD_SET(listen_fd, &active_fd_set);
    
    while (1) {
        read_fd_set = active_fd_set;
        if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0) {
            consoleLogger.LPut(LOGGER_FULL_ERR "select()");
            exit(1);
        }
        
        for (int i = 0; i < FD_SETSIZE; ++i) {
            if (FD_ISSET(i, &read_fd_set)) {
                if (i == listen_fd) {
                    // connection request on original socket
                    int new;
                    size = sizeof (clientname);
                    new = accept(listen_fd, (struct sockaddr *) &clientname, &size);
                    if (new < 0) {
                        consoleLogger.LPut(LOGGER_FULL_ERR "accept()");
                        exit(1);
                    }
                    consoleLogger.LPut(LOGGER_FULL_OK "accept()");
                    FD_SET(new, &active_fd_set);
                }
                else {
                    if (ReadFromClient(i) < 0) {
                        consoleLogger.LPut(LOGGER_FULL_ERR "ReadFromClient()");
                        close(i);
                        FD_CLR(i, &active_fd_set);
                        continue;
                    }
                    if (WriteToClient(i) < 0) {
                        consoleLogger.LPut(LOGGER_FULL_ERR "WriteToClient()");
                        close(i);
                        FD_CLR(i, &active_fd_set);
                        continue;
                    }
                    
                    consoleLogger.LPut(LOGGER_FULL_OK "Close");
                    close(i);
                    FD_CLR(i, &active_fd_set);
                }
            }
        }
    }
    
    
    /**--------------------**/
    
    
    
    
    //FD_SET(listen_fd, )
    
    
    return 0;
}