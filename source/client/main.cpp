#include "client.h"

int main (int argc, char** argv)
{
	Client cl(AF_INET, 2021, 2020, argv[1]);

	switch(argc)
	{
		case 4:
			cl.send_command(argv[2], argv[3]);
			break;
		case 5:
			cl.send_command(argv[2], argv[3], argv[4]);
			break;
		default:
			std::cout << "Input error\nExample: ./client 127.0.0.1 sendfile makefile testdir";
			break;
	}
	return 0;
}
