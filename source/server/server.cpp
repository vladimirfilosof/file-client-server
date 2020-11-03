#include "server.h"

Server::Server(int domain, unsigned short int data_port, unsigned short int manage_port, const char* ip)
{
	sa.sin_family = domain;
	sa.sin_port = htons(manage_port);
	inet_pton(domain, ip, &(sa.sin_addr));

	manage_listner = socket(domain, SOCK_STREAM, 0);
	bind (manage_listner, (const sockaddr*)&(sa), sizeof(sa));

	sa.sin_port = htons(data_port);
	data_listner = socket(domain, SOCK_STREAM, 0);
	bind(data_listner, (const sockaddr*)&(sa), sizeof(sa));
}

Server::~Server()
{
	close(data_sock);
}

void Server::manage_signal_handler() 
{
	uint32_t sizes[5];
	uint32_t file_length = 0;
	char *buf, *command_name, *file_name, *file_dir;
	listen(manage_listner, 1);
	listen(data_listner, 1);
	while (true)
	{
		manage_sock = accept(manage_listner, nullptr, nullptr);
		while (true)
		{
			// message: message_length, command_length, filename_length, filedir_length, file_length
			int bytes_read = recv(manage_sock, sizes, sizeof(sizes), 0);
			if (bytes_read <= 0) break;
			std::cout << "[Manage message]\n";
			std::cout << "First message (sizes):" << std::endl;
			for (int i = 0; i < 4; ++i)
				std::cout << "[" << i << "]: " << sizes[i] << std::endl;

			buf = new char[ sizes[0] ];

			// message: command_name, filename, filedir
			bytes_read = recv(manage_sock, buf, sizes[0], 0);
			if (bytes_read <= 0) 
			{
				delete[] buf;
				break;
			}

			std::cout << "Second manage message (commands):" << std::endl;
			command_name = new char[ sizes[1] ];
			file_name = new char[ sizes[2] ];
			file_dir = new char[ sizes[3] ];
			file_length = sizes[4];

			memcpy(command_name, buf, sizes[1]);
			memcpy(file_name, buf + sizes[1], sizes[2]);
			memcpy(file_dir, buf + sizes[1] + sizes[2], sizes[3]);

			std::cout << "Message text: ";
			for (uint32_t i = 0; i < sizes[0]; ++i) 
				std::cout << buf[i];
			std::cout << std::endl;

			std::cout << "Command: ";
			for (uint32_t i = 0; i < sizes[1]; ++i) 
				std::cout << command_name[i];
			std::cout << std::endl;

			std::cout << "File name: ";
			for (uint32_t i = 0; i < sizes[2]; ++i) 
				std::cout << file_name[i];
			std::cout << std::endl;

			std::cout << "File dir on server: ";
			for (uint32_t i = 0; i < sizes[3]; ++i) 
				std::cout << file_dir[i];
			std::cout << std::endl;

			std::cout << "File size: " << file_length << std::endl;

			std::cout << std::endl;
			if (!strcmp(command_name, "sendfile") && file_length)
				get_file(file_dir, file_name, file_length);
		}
		close(manage_sock);
	}
}

int Server::get_file(const char* file_dir, const char* file_name, int file_size)
{

	bool is_get = false;
	char* buf = new char[file_size];

	while (!is_get)
	{
		data_sock = accept(data_listner, nullptr, nullptr);
		int bytes_read = recv(data_sock, buf, file_size, 0); 
		if (bytes_read <= 0) break;

		std::cout << "[Data message]\n";
		for (int i = 0; i < file_size; ++i)
			std::cout << buf[i];

		is_get = true;
	}
	close(data_sock);

	return 1;
}
