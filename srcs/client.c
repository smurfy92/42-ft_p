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

int		check_if_data(t_mem *mem)
{
	char	**tabl;
	int		fd;
	int i;

	tabl = ft_strsplit(mem->data, ' ');
	if (ft_strequ(tabl[0], "data") == 1 && tabl[1] && tabl[2])
	{
		fd = open(tabl[1], O_RDWR | O_CREAT, 0666);
		i = 4 + 2 + ft_strlen(tabl[1]) - 1;
		while (++i < mem->len)
			write(fd, &mem->data[i], 1);
	}
	else
		return (-1);
	return (0);
}

int check_put(int fd, t_mem *mem)
{
	t_mem	*tmp;
	int		file;
	char	**tabl;

	tmp = NULL;
	tmp = (t_mem*)malloc(sizeof(t_mem));
	tabl = ft_strsplit(mem->data, ' ');
	if (!tabl[1])
	{
		write_error("put", "please specify a file", fd);
	}
	else
	{
		file = open(tabl[1], O_RDONLY);
		if (file < 0)
			return (write_error("put", "file doesnt exists", fd));
		tmp->data = ft_strjoin("data ", tabl[1]);
		tmp->data = ft_strjoin_nf(tmp->data, " ", 1);
		tmp->len = ft_strlen(tmp->data);
		mem = read_fd(file);
		mem = ft_memjoin(tmp, mem);
		write_fd(fd, mem);
	}
	return (0);
}

void	loop(int socket)
{
	t_mem  *mem;
	t_mem  *mem2;

	mem = NULL;
	while (42)
	{
		mem = prompt();
		if (ft_strequ(mem->data, "quit"))
			break ;
		if (!ft_strequ(mem->data, "put") && check_put(socket, mem) != 0)
		{
			send(socket, mem->data, mem->len, 0);
			ft_strdel(&mem->data);
			mem2 = read_fd(socket);
			if (check_if_data(mem2) == -1)
				ft_putstr(mem2->data);
			ft_strdel(&mem2->data);
		}

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
