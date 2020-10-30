#ifndef CLIENT_H
#define CLIENT_N

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <filesystem>

class Client
{
public:
	Client(int domain, unsigned short int data_port, unsigned short int manage_port, const char* ip);
	~Client();
	
	int send_command(const char* com);


private:
	int manage_sock, data_sock;
	sockaddr_in sa;
};

#endif
