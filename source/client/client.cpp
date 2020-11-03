#include "client.h"

namespace fs = std::filesystem;

Client::Client(int domain, unsigned short int data_port, unsigned short int manage_port, const char* ip) 
{
	sa_manage.sin_family = domain;
	sa_manage.sin_port = htons(manage_port);
	inet_pton(domain, ip, &(sa_manage.sin_addr)); 

	manage_sock = socket(domain, SOCK_STREAM, 0);
	
	sa_data = sa_manage;
	sa_data.sin_port = htons(data_port);

	data_sock = socket(domain, SOCK_STREAM, 0);
}

Client::~Client() 
{
	close(manage_sock);
}

int Client::send_command(const char* command, const char* file_path, const char* file_dir) 
{
	if ( connect(manage_sock, (const sockaddr *)&(sa_manage), sizeof(sa_manage)) )
		std::cerr << "Manage connection error" << std::endl;

	fs::path p(file_path);

	const char* file_name = p.filename().c_str();
	std::ifstream file(p);
	int file_size = fs::file_size(p);

	int sizes[5]; //message length, command length, file name length, file dir length, file_length

	sizes[0] = 0;
	sizes[1] = strlen(command);
	sizes[2] = strlen(file_name);
	sizes[3] = strlen(file_dir);
	
	sizes[4] = file_size;

	for (int i = 1; i < 4; ++i)
	{
		sizes[0] += sizes[i];
	}

	char* buf = new char[ sizes[0] ];

	memcpy(buf, command, sizes[1]);
	memcpy(buf + sizes[1], file_name, sizes[2]);
	memcpy(buf + sizes[1] + sizes[2], file_dir, sizes[3]);
	
	std::cout << "Message in manage socket: ";
	for (int i = 0; i < sizes[0]; ++i) std::cout << buf[i];
	std::cout << std::endl;

	char* file_buf = new char[ sizes[4] ];
	file.read(file_buf, file_size);

	send(manage_sock, sizes, sizeof(sizes), 0);
	send(manage_sock, buf, sizeof(buf), 0);

	send_file(file_buf, file_size);
	return 1;
}

int Client::send_file(const char* file_data, int data_size)
{
	while ( connect(data_sock, (const sockaddr *)&(sa_data), sizeof(sa_data)) )
		std::cerr << "Data connection error" << std::endl;

	send(data_sock, file_data, data_size, 0);

	return 1;
}

