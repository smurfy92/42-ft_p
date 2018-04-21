/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 12:04:45 by jtranchi          #+#    #+#             */
/*   Updated: 2018/04/21 14:59:51 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"
#include "errno.h"

void		print_usage(void)
{
	ft_putendl("usage : serveur <port>");
	exit(0);
}


int		ft_create_client(char *addr, int port)
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
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		printf("connect error\n");
		printf("err -> %s\n",strerror(errno));
		exit(-1);
	}
	return (sock);

}

void remove_back(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			str[i] = ' ';
}

int main(int argc, char **argv)
{
	int port;
	int socket;
	char *buf;
	int r;
	char buf2[1024];
	int t;


	t = 0;
	if (argc <= 2)
		print_usage();
	port = atoi(argv[2]);
	socket = ft_create_client(argv[1], port);
	while (42)
	{
		ft_putstr("$> ");
		get_next_line(0 ,&buf);
		ft_putstr("buf ->");
		ft_putendl(buf);
		write(socket, buf, sizeof(buf));
		while ((r = read(socket, buf2, 1024)))
		{
			ft_putstr("recv buf -> ");
			remove_back(buf2);
			ft_putstr(buf2);
		}
		ft_bzero(buf2 , 1024);
		// while (get_next_line(socket ,&buf) > 0)
		// {
		// 	ft_putstr(buf);
		// 	ft_putchar(' ');
		// }
		// ft_putchar('\n');
	}


		// while ((r = read(socket, buf , 1024)))
		// 	ft_putendl(buf);
		// ft_bzero(buf , 1024);
	close(socket);
}