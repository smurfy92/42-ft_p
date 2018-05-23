/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:15:11 by jtranchi          #+#    #+#             */
/*   Updated: 2018/05/12 15:15:12 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftp.h"

void		print_usage(void)
{
	ft_putendl("usage : serveur <port>");
	exit(0);
}

char		*get_address(char *addr)
{
	struct hostent *host;

	host = gethostbyname(addr);
	if (!host)
	{
		ft_putendl("ERROR: not known host");
		exit(-1);
	}
	return (inet_ntoa(*(struct in_addr*)(host->h_addr_list[0])));
}

t_mem		*prompt(void)
{
	t_mem *mem;

	ft_putstr("$> ");
	mem = read_fd(0);
	return (mem);
}

int			check_if_data(t_mem *mem)
{
	char	**tabl;
	int		fd;
	int		i;
	int		ret;

	ret = -1;
	tabl = ft_strsplit(mem->data, ' ');
	if (ft_strequ(tabl[0], "data") == 1 && tabl[1])
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
