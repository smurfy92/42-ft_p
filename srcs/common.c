/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:31:24 by jtranchi          #+#    #+#             */
/*   Updated: 2018/05/12 15:31:59 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"
#include "../includes/serveur.h"

char	*read_fd(int fd)
{
	int		r;
	int		total;
	char	*tmp;
	char	*buf;

	buf = ft_strnew(BUFFER + 1);
	tmp = ft_strdup("");
	total = 0;
	while ((r = read(fd, buf, BUFFER)))
	{
		total += r;
		buf[BUFFER] = 0;
		tmp = ft_strjoin_nf(tmp, buf, 1);
		ft_bzero(buf, BUFFER);
		if (r < BUFFER)
			break ;
	}
	printf("total - > %d \n", total);
	ft_strdel(&buf);
	return (tmp);
}
