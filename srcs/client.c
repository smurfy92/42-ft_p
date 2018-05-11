/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 12:04:45 by jtranchi          #+#    #+#             */
/*   Updated: 2018/04/28 13:51:21 by jtranchi         ###   ########.fr       */
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
			str[i] = 0;
}

int check_if_data(char *str)
{
	char **tabl;

	tabl = ft_strsplit(str, ' ');
	if (ft_strequ(tabl[0], "data") == 1 && tabl[1] && tabl[2]) {
		printf("filename -> %s\n", tabl[1]);

		int fd = open(tabl[1], O_RDWR | O_CREAT, 0666);
		printf("fd -> %d\n", fd);
		write(fd, &str[4 + 2 + ft_strlen(tabl[1])], ft_strlen(&str[4 + 2 + ft_strlen(tabl[1])]));
	} else {

		return (-1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	int port;
	int socket;
	char *buf;
	char *tmp;
	int t;


	t = 0;
	if (argc <= 2)
		print_usage();
	port = atoi(argv[2]);
	socket = ft_create_client(argv[1], port);
	buf = ft_strnew(1025);
	while (42)
	{
		tmp = ft_strdup("");
		ft_putstr("$> ");
		read(0, buf, 1024);
		remove_back(buf);
		send(socket, buf, ft_strlen(buf), 0);
		if (ft_strequ(buf, "quit"))
			break ;
		ft_bzero(buf , 1024);
		while ((t = recv(socket, buf, 1024, 0))){
			buf[1024] = 0;
			tmp = ft_strjoin(tmp, buf);
			ft_bzero(buf, 1024);
			if (t < 1024)
				break ;
		}
		if (check_if_data(tmp) == -1)
			ft_putstr(tmp);
		ft_bzero(buf , 1024);
	}
	close(socket);
}