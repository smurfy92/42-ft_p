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

#include "../includes/serveur.h"

int		check_if_data(t_buf *buf)
{
	char	**tabl;
	int		fd;
	int i;

	tabl = ft_strsplit(buf->str, ' ');
	if (ft_strequ(tabl[0], "data") == 1 && tabl[1] && tabl[2])
	{
		fd = open(tabl[1], O_RDWR | O_CREAT, 0666);
		i = 4 + 2 + ft_strlen(tabl[1]) - 1;
		while (++i < buf->len)
			write(fd, &buf->str[i], 1);
	}
	else
		return (-1);
	return (0);
}

void	loop(int socket)
{
	t_buf  *buf;

	buf = NULL;
	while (42)
	{
		buf = prompt();
		if (ft_strequ(buf->str, "quit"))
			break ;
		send(socket, buf->str, buf->len, 0);
		ft_strdel(&buf->str);
		buf = read_fd(socket);
		printf("len -> %d\n", buf->len);
		if (check_if_data(buf) == -1)
			ft_putstr(buf->str);
		ft_strdel(&buf->str);
	}
	ft_strdel(&buf->str);
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
