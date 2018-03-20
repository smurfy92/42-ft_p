#include "../includes/ft_p.h"

void		print_usage(void)
{
	ft_putendl("usage : serveur <port>");
	exit(0);
}


int		ft_create_serveur(int port)
{
	int sock;
	struct protoent *p;
	struct sockaddr_in sin;

	p = getprotobyname("tcp");
	if (p == 0)
	{
		printf("proto error\n");
		exit(-1);
	}
	sock = socket(PF_INET, SOCK_STREAM, p->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htons(INADDR_ANY);
	if (bind(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		printf("bind error\n");
		exit(-1);
	}
	listen(sock, 42);
	return (sock);

}

int main(int argc, char **argv)
{
	int port;
	int socket;
	int cs;
	struct sockaddr sin;
	unsigned int sizesin;

	if (argc <= 1)
		print_usage();
	port = atoi(argv[1]);
	socket = ft_create_serveur(port);
	cs = accept(socket, &sin, &sizesin);
	close(cs);
	close(socket);
}