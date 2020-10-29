#include "server.h"

int main(int argc, char** argv)
{
	Server srv(AF_INET, 2021, 2020, "0.0.0.0");
	srv.manage_signal_handler();

	return 0;
}

Server::Server(int domain, unsigned short int data_port, unsigned short int manage_port, const char* ip)
{
	sa.sin_family = domain;
	sa.sin_port = htons(manage_port);
	inet_pton(domain, ip, &(sa.sin_addr));

	manage_listner = socket(domain, SOCK_STREAM, 0);
	bind (manage_listner, (const sockaddr*)&(sa), sizeof(sa));

	sockaddr_in sa2 = sa;

	sa2.sin_port = htons(data_port);

	data_listner = socket(domain, SOCK_STREAM, 0);
	bind(data_listner, (const sockaddr*)&(sa2), sizeof(sa2));
}

int Server::manage_signal_handler() 
{
	char mess[128];
	listen(manage_listner, 1);
	listen(data_listner, 1);
	while (true)
	{
		manage_sock = accept(manage_listner, nullptr, nullptr);
		while (true)
		{
			int bytes_read = recv(manage_sock, &mess, 128, 0);
			if (bytes_read <= 0)
				break;
			else
				for (int i = 0; i < bytes_read; ++i)
					std::cout << mess[i];
		}
		close(manage_sock);
	}

	
	return 1;
}

Server::~Server()
{
	close(data_sock);
}
