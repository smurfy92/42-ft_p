/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 11:57:35 by jtranchi          #+#    #+#             */
/*   Updated: 2018/04/28 13:57:12 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftp.h"

int		ft_create_serveur(int port)
{
	int					sock;
	struct protoent		*p;
	struct sockaddr_in	sin;

	p = getprotobyname("tcp");
	if (p == 0)
	{
		ft_putendl("proto error");
		exit(-1);
	}
	sock = socket(PF_INET, SOCK_STREAM, p->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		ft_putendl("bind error\n");
		exit(-1);
	}
	listen(sock, 42);
	return (sock);
}

int		check_builtin(t_mem *mem, int fd)
{
	char **tabl;

	tabl = ft_strsplit(mem->data, ' ');
	if (ft_strequ(tabl[0], "ls") == 1)
		return (exec_ls(tabl, fd));
	if (ft_strequ(tabl[0], "pwd") == 1)
		return (exec_pwd(fd));
	if (ft_strequ(tabl[0], "quit") == 1)
		exit(0);
	if (ft_strequ(tabl[0], "get") == 1)
		return (exec_get(tabl, fd));
	if (ft_strequ(tabl[0], "data") == 1)
		return (check_if_data(mem));
	return (-1);
}

void	create_client(int cs)
{
	t_mem	*mem;
	int		f;

	f = fork();
	if (f == 0)
	{
		while (42)
		{
			mem = read_fd(cs);
			printf("cs -> %d buf -> %s\n", cs, mem->data);
			if (check_builtin(mem, cs) == -1)
				write(cs, "", 1);
		}
	}
}

int		main(int argc, char **argv)
{
	int					port;
	int					socket;
	int					cs;
	struct sockaddr		sin;
	unsigned int		sizesin;

	if (argc <= 1)
		print_usage();
	port = atoi(argv[1]);
	socket = ft_create_serveur(port);
	while (42)
	{
		cs = accept(socket, &sin, &sizesin);
		printf("accepted -> %d\n", cs);
		create_client(cs);
	}
	close(socket);
}
