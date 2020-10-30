#include "client.h"

Client::Client(int domain, unsigned short int data_port, unsigned short int manage_port, const char* ip) 
{
	sa.sin_family = domain;
	sa.sin_port = htons(manage_port);
	inet_pton(domain, ip, &(sa.sin_addr)); 

	manage_sock = socket(domain, SOCK_STREAM, 0);
	
	if ( connect(manage_sock, (const sockaddr *)&(sa), sizeof(sa)) )
	{
		std::cerr << "Manage connection error" << std::endl;
	}

	sa.sin_port = htons(data_port);

//	if ( connect(data_sock, (const sockaddr *)&(sa), sizeof(sa)) )
//		std::cerr << "Data connection error" << std::endl;
}

Client::~Client() 
{
	close(manage_sock);
}

int Client::send_command(const char* com) 
{

	char buf[] = "getfilesome file/";

	unsigned int num[4];
	num[0] = sizeof(buf);
	num[1] = 7;
	num[2] = 9;
	num[3] = 1;

	send(manage_sock, num, sizeof(num), 0);
	send(manage_sock, buf, sizeof(buf), 0);
	return 1;
}
