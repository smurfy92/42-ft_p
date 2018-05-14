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

#include "../includes/serveur.h"

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

void		remove_back(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			str[i] = 0;
}

t_buf		*prompt()
{
	t_buf *tmp;

	ft_putstr("$> ");
	tmp = read_fd(0);
	remove_back(tmp->str);
	return (tmp);
}
