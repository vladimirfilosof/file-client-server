#include <iostream>

#include "server.h"

int main(int argc, char** argv)
{
	Server srv(AF_INET, 2021, 2020, "0.0.0.0");
	srv.manage_signal_handler();

	return 0;
}
