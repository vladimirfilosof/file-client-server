#ifndef SERVER_H
#define SERVER_H

#include <fstream>
#include <iostream>
#include <filesystem>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Server
{
public:
	Server(int domain, unsigned short int data_port, unsigned short int manage_port, const char* ip);
	~Server();

	int manage_signal_handler();

private:
	int data_listner, manage_listner, data_sock, manage_sock;
	sockaddr_in sa;
};

#endif
