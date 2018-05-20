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

void		remove_back(t_mem *mem)
{
	int i;

	i = -1;
	while (++i < mem->len)
	{
		if (mem->data[i] == '\n')
		{
			mem->data[i] = 0;
			break ;
		}
	}
	mem->len = i;
}

t_mem		*prompt(void)
{
	t_mem *mem;

	ft_putstr("$> ");
	mem = read_fd(0);
	remove_back(mem);
	return (mem);
}
