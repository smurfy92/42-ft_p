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
	char	*tmp;
	char	*buf;

	buf = ft_strnew(1025);
	tmp = ft_strdup("");
	while ((r = read(fd, buf, BUFFER)))
	{
		buf[BUFFER] = 0;
		tmp = ft_strjoin_nf(tmp, buf, 3);
		ft_bzero(buf, BUFFER);
		if (r < BUFFER)
			break ;
	}
	return (tmp);
}
