#include "client.h"

int main (int argc, char** argv)
{
	Client cl(AF_INET, 2021, 2020, "127.0.0.1");
	cl.send_command("com");

	return 0;
}
