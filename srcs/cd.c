/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:38:28 by jtranchi          #+#    #+#             */
/*   Updated: 2018/05/16 15:38:29 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftp.h"

char	*remove_last_dir(char *wd)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = ft_strlen(wd);
	while (wd[i] != '/')
		i--;
	ret = ft_strnew(i);
	ft_memcpy(ret, wd, i);
	return (ret);
}

char	*parse_wd(char *wd, char *buf)
{
	char	**tabl;
	int		i;

	i = -1;
	tabl = ft_strsplit(buf, '/');
	while (tabl[++i])
	{
		if (ft_strequ(tabl[i], "..") == 1)
			wd = remove_last_dir(wd);
		else
		{
			wd = ft_strjoin(wd, "/");
			wd = ft_strjoin(wd, tabl[i]);
		}
	}
	return (wd);
}

int		check_if_contains(char *wd, char *newwd)
{
	int i;

	i = -1;
	while (wd[++i])
		if (wd[i] != newwd[i])
			return (0);
	return (1);
}

int		exec_cd(t_mem *mem, char *wd, int socket)
{
	char	**tabl;
	char	*newwd;
	char	*curwd;

	tabl = ft_strsplit(mem->data, ' ');
	curwd = NULL;
	newwd = NULL;
	curwd = getcwd(curwd, 0);
	if (!tabl[1])
		chdir(wd);
	else if (tabl[1][0] != '.' && tabl[1][0] != '/')
	{
		curwd = ft_strjoin(curwd, "/");
		curwd = ft_strjoin(curwd, tabl[1]);
		chdir(curwd);
	}
	else
	{
		newwd = parse_wd(curwd, tabl[1]);
		if (check_if_contains(wd, newwd))
			chdir(newwd);
	}
	ft_free_tabl(tabl);
	write(socket, "", 1);
	return (0);
}

int		exec_lcd(t_mem *mem, char *wd)
{
	char	**tabl;
	char	*newwd;
	char	*curwd;

	tabl = ft_strsplit(mem->data, ' ');
	curwd = NULL;
	newwd = NULL;
	curwd = getcwd(curwd, 0);
	if (!tabl[1])
		chdir(wd);
	else if (tabl[1][0] != '.' && tabl[1][0] != '/')
	{
		curwd = ft_strjoin(curwd, "/");
		curwd = ft_strjoin(curwd, tabl[1]);
		chdir(curwd);
	}
	else if (tabl[1][0] == '.' || tabl[1][0] == '/')
		chdir(tabl[1]);
	else
	{
		newwd = parse_wd(curwd, tabl[1]);
		chdir(newwd);
	}
	ft_free_tabl(tabl);
	return (0);
}
