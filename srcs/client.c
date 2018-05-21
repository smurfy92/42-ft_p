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

#include "../includes/ftp.h"

int		check_if_data(t_mem *mem)
{
	char	**tabl;
	int		fd;
	int		i;
	int		ret;

	ret = -1;
	tabl = ft_strsplit(mem->data, ' ');
	if (ft_strequ(tabl[0], "data") == 1 && tabl[1] && tabl[2])
	{
		fd = open(tabl[1], O_RDWR | O_CREAT, 0666);
		i = 4 + 2 + ft_strlen(tabl[1]) - 1;
		while (++i < mem->len)
			write(fd, &mem->data[i], 1);
		ret = 0;
		close(fd);
	}
	ft_free_tabl(tabl);
	return (ret);
}

int		check_put(int fd, t_mem **mem)
{
	t_mem	*tmp;
	int		file;
	char	**tabl;

	tmp = NULL;
	tmp = (t_mem*)malloc(sizeof(t_mem));
	tabl = ft_strsplit((*mem)->data, ' ');
	if (!tabl[1])
		write_error("put", "please specify a file", fd);
	else
	{
		if ((file = open(tabl[1], O_RDONLY)) < 0)
		{
			ft_free_tabl(tabl);
			return (write_error("put", "file doesnt exists", fd));
		}
		tmp->data = ft_strjoin("data ", tabl[1]);
		tmp->data = ft_strjoin_nf(tmp->data, " ", 1);
		tmp->len = ft_strlen(tmp->data);
		*mem = read_fd(file);
		close(file);
		*mem = ft_memjoin(tmp, *mem);
	}
	ft_free_tabl(tabl);
	return (0);
}

void	loop(int socket)
{
	t_mem	*mem;
	t_mem	*mem2;
	char	**tabl;

	mem = NULL;
	while (42)
	{
		mem = prompt();
		tabl = ft_strsplit(mem->data, ' ');
		if (ft_strequ(tabl[0], "quit") == 1)
			break ;
		if (ft_strequ(tabl[0], "put") == 1)
			check_put(socket, &mem);
		if (mem->len > 0)
		{
			write_fd(socket, mem);
			mem2 = read_fd(socket);
			if (check_if_data(mem2) == -1)
				ft_putstr(mem2->data);
			ft_free_mem(mem2);
		}
		ft_free_tabl(tabl);
		ft_free_mem(mem);
	}
}

int		ft_create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*p;
	struct sockaddr_in	sin;

	p = getprotobyname("tcp");
	if (p == 0)
	{
		write_error("connection", "protocol error", 1);
		exit(-1);
	}
	sock = socket(PF_INET, SOCK_STREAM, p->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(get_address(addr));
	if (connect(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		write_error("connection", "connect error", 1);
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
