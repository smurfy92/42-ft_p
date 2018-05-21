/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 13:11:06 by jtranchi          #+#    #+#             */
/*   Updated: 2018/05/21 13:11:07 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftp.h"

void	ft_free_tabl(char **tabl)
{
	int i;

	i = -1;
	while (tabl[++i])
		ft_strdel(&tabl[i]);
	free(tabl);
}

void	ft_free_mem(t_mem *mem)
{
	ft_strdel(&mem->data);
	free(mem);
}

int		write_error(char *cmd, char *err, int fd)
{
	char *str;

	str = ft_strjoin("ERROR: ", cmd);
	str = ft_strjoin_nf(str, ": ", 1);
	str = ft_strjoin_nf(str, err, 1);
	str = ft_strjoin_nf(str, "\n", 1);
	write(fd, str, ft_strlen(str));
	ft_strdel(&str);
	return (-1);
}
