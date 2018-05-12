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

#include "../includes/client.h"

int		check_if_data(char *str)
{
	char	**tabl;
	char	*tmp;
	int		fd;

	tabl = ft_strsplit(str, ' ');
	if (ft_strequ(tabl[0], "data") == 1 && tabl[1] && tabl[2])
	{
		fd = open(tabl[1], O_RDWR | O_CREAT, 0666);
		tmp = &str[4 + 2 + ft_strlen(tabl[1])];
		printf("fd -> %d\n", fd);
		write(fd, tmp, ft_strlen(tmp));
	}
	else
		return (-1);
	return (0);
}

void	loop(int socket)
{
	char *buf;
	char *tmp;

	buf = ft_strnew(BUFFER);
	while (42)
	{
		prompt(buf);
		if (ft_strequ(buf, "quit"))
			break ;
		send(socket, buf, ft_strlen(buf), 0);
		ft_bzero(buf, BUFFER);
		tmp = read_fd(socket);
		if (check_if_data(tmp) == -1)
			ft_putstr(tmp);
		ft_bzero(buf, BUFFER);
	}
}

int			ft_create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*p;
	struct sockaddr_in	sin;

	p = getprotobyname("tcp");
	if (p == 0)
	{
		ft_putendl("ERROR: protocol error");
		exit(-1);
	}
	sock = socket(PF_INET, SOCK_STREAM, p->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	;
	sin.sin_addr.s_addr = inet_addr(get_address(addr));
	if (connect(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		ft_putendl("ERROR: connection error");
		exit(-1);
	}
	return (sock);
}

int		main(int argc, char **argv)
{
	int port;
	int socket;

	if (argc <= 2)
		print_usage();
	port = atoi(argv[2]);
	socket = ft_create_client(argv[1], port);
	loop(socket);
	close(socket);
}
