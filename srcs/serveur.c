

#include "../includes/ft_p.h"

void		print_usage(void)
{
	ft_putendl("usage : serveur <port>");
	exit(0);
}


int main(int argc, char **argv)
{
	int port;

	if (argc <= 1)
		print_usage();
	port = atoi(argv[1]);
}