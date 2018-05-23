/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:31:24 by jtranchi          #+#    #+#             */
/*   Updated: 2018/05/23 18:45:36 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftp.h"

t_mem	*read_fd(int fd)
{
	t_mem	*mem;
	t_mem	*buf;

	mem = NULL;
	buf = (t_mem *)malloc(sizeof(t_mem));
	buf->data = ft_strnew(BUFFER + 1);
	buf->len = 0;
	while ((buf->len = read(fd, buf->data, BUFFER)))
	{
		mem = ft_memjoin(mem, buf);
		ft_bzero(buf->data, buf->len);
		if (buf->len < BUFFER)
			break ;
		buf->len = 0;
	}
	ft_free_mem(buf);
	return (mem);
}

void	write_fd(int fd, t_mem *mem)
{
	int i;

	i = -1;
	while (++i * BUFFER < mem->len)
	{
		if (mem->len - (i * BUFFER) < 1024)
			write(fd, &mem->data[i * BUFFER], mem->len - (i * BUFFER));
		else
			write(fd, &mem->data[i * BUFFER], BUFFER);
	}
}

t_mem	*ft_memjoin(t_mem *dest, t_mem *src)
{
	t_mem *ret;

	ret = (t_mem *)malloc(sizeof(t_mem));
	if (!dest)
	{
		ret->data = ft_strnew(src->len);
		ft_memcpy(ret->data, src->data, src->len);
		ret->len = src->len;
		return (ret);
	}
	ret->len = dest->len + src->len;
	ret->data = ft_strnew(ret->len);
	ft_memcpy((void*)ret->data, dest->data, dest->len);
	ft_memcpy((void*)&ret->data[dest->len], src->data, src->len);
	ft_free_mem(dest);
	return (ret);
}
