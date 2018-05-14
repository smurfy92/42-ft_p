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

#include "../includes/serveur.h"

t_buf	*read_fd(int fd)
{
	int		r;
	t_buf	*tmp;
	char	*buf;
	void 	*test;

	buf = ft_strnew(BUFFER + 1);
	tmp = (t_buf *)malloc(sizeof(t_buf));

	tmp->str = ft_strdup("");
	tmp->len = 0;
	while ((r = read(fd, buf, BUFFER)))
	{
		buf[r] = 0;
		test = ft_strnew(tmp->len + r + 1);
		ft_memcpy(test, tmp->str, tmp->len);
		ft_memcpy(&test[tmp->len], buf, r);
		tmp->len += r;
		ft_strdel(&tmp->str);
		tmp->str = ft_strnew(tmp->len);
		ft_memcpy(tmp->str, test, tmp->len);
		tmp->str[tmp->len + 1] = 0;
		ft_bzero(buf, BUFFER);
		if (r < BUFFER)
			break ;
	}
	ft_strdel(&buf);
	return (tmp);
}


void	write_fd(int fd, t_buf *buf)
{
	int i;

	i = -1;
	while (++i < buf->len)
		write(fd, &buf->str[i], 1);
	write(fd, "\n", 1);
}
