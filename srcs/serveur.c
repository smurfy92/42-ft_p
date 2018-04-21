/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 11:57:35 by jtranchi          #+#    #+#             */
/*   Updated: 2018/04/21 15:29:20 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		printf("bind error\n");
		exit(-1);
	}
	listen(sock, 42);
	return (sock);

}


void  check_builtin(char *str, int fd)
{
	char **tab;
	int fds[2];

	pipe(fds);
	tab = ft_strsplit(str, ' ');
	if (ft_strcmp(tab[0], "ls") == 0)
	{
		int f = fork();
		if (f == 0) {
			dup2(fds[0], 1);
			dup2(fds[1], fd);
			execve("/bin/ls", tab, NULL);
		}
		wait(0);
		close(fds[1]);
		close(fds[0]);
	}
}

int main(int argc, char **argv)
{
	int port;
	int socket;
	int cs;
	struct sockaddr sin;
	unsigned int sizesin;
	char buf[1024];
	int r;

	int t;

	t = 0;
	if (argc <= 1)
		print_usage();
	port = atoi(argv[1]);
	socket = ft_create_serveur(port);
	cs = accept(socket, &sin, &sizesin);
	while (42)
	{
		// ft_putstr("ici");
		// get_next_line(cs ,&buf);
		// ft_putstr("buf -> ");
		// ft_putendl(buf);
		while ((r = read(cs, buf, 1024)))
		{
			ft_putstr("buf -> ");
			ft_putendl(buf);
			check_builtin(buf, cs);
			ft_bzero(buf, 1024);
		}
	}
	close(socket);
}