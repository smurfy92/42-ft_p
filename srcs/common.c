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

t_mem	*read_fd(int fd)
{
	int		r;
	t_mem	*mem;
	char	*buf;
	void 	*test;

	buf = ft_strnew(BUFFER + 1);
	mem = (t_mem *)malloc(sizeof(t_mem));

	mem->data = ft_strdup("");
	mem->len = 0;
	int total = 0;
	while ((r = read(fd, buf, BUFFER)))
	{
		buf[r] = 0;
		total += r;
		test = ft_strnew(mem->len + r + 1);
		ft_memcpy(test, mem->data, mem->len);
		ft_memcpy(&test[mem->len], buf, r);
		mem->len += r;
		ft_strdel(&mem->data);
		mem->data = ft_strnew(mem->len);
		ft_memcpy(mem->data, test, mem->len);
		mem->data[mem->len + 1] = 0;
		ft_bzero(buf, BUFFER);
		if (r < BUFFER)
			break ;
	}
	printf("total read -> %d\n", total);
	ft_strdel(&buf);
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
	printf("total write -> %d\n", mem->len);
}


t_mem	*ft_memjoin(t_mem *dest, t_mem *src)
{
	t_mem *ret;

	ret = (t_mem *)malloc(sizeof(t_mem));
	ret->len = dest->len + src->len;
	ret->data = ft_strnew(ret->len);
	ft_memcpy((void*)ret->data , dest->data, dest->len);
	ft_memcpy((void*)&ret->data[dest->len], src->data, src->len);
	return (ret);
}