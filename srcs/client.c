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
#include <errno.h>

void	check_put2(char **tabl, t_mem *tmp, t_mem **mem)
{
	int		file;

	if ((file = open(tabl[1], O_RDONLY)) < 0)
	{
		ft_free_tabl(tabl);
		write_error("put", "file doesnt exists", 2);
	}
	tmp->data = ft_strjoin("data ", tabl[1]);
	tmp->data = ft_strjoin_nf(tmp->data, " ", 1);
	tmp->len = ft_strlen(tmp->data);
	if (tabl[2])
		*mem = ft_memjoin(tmp, read_fd(file));
	else
		*mem = tmp;
	close(file);
}

int		check_put(t_mem **mem)
{
	t_mem	*tmp;
	char	**tabl;

	tmp = NULL;
	tmp = (t_mem*)malloc(sizeof(t_mem));
	remove_back(*mem);
	tabl = ft_strsplit((*mem)->data, ' ');
	if (!tabl[1])
		write_error("put", "please specify a file", 2);
	else
		check_put2(tabl, tmp, mem);
	ft_free_tabl(tabl);
	return (0);
}

void	loop(int socket)
{
	t_mem	*mem;
	t_mem	*mem2;
	char	**tabl;
	char	*wd;

	mem = NULL;
	wd = NULL;
	wd = getcwd(wd, 0);
	while (42)
	{
		mem = prompt();
		remove_back(mem);
		tabl = ft_strsplit(mem->data, ' ');
		if (ft_strequ(tabl[0], "quit") == 1)
			break ;
		if (ft_strequ(tabl[0], "put") == 1)
			check_put(&mem);
		if (ft_strequ(tabl[0], "lls") == 1)
			exec_lls(&mem, tabl);
		if (ft_strequ(tabl[0], "lpwd") == 1)
			exec_lpwd(&mem);
		if (ft_strequ(tabl[0], "lcd") == 1)
			exec_lcd(mem, wd);
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
	struct sockaddr_in6	sin;

	p = getprotobyname("tcp");
	if (p == 0)
	{
		write_error("connection", "protocol error", 1);
		exit(-1);
	}
	sock = socket(AF_INET6, SOCK_STREAM, p->p_proto);
	sin.sin6_family = AF_INET6;
	sin.sin6_port = htons(port);
	inet_pton(AF_INET6, addr, &sin.sin6_addr);
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
