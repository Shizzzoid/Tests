#ifndef SERVER_H
#define SERVER_H

#include <string>

void start_server(int port);
void handle_client(int client_socket);

#endif
