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

void	ft_chdir(char *wd, char *cmd, int fd)
{
	t_mem *tmp;

	tmp = (t_mem *)malloc(sizeof(t_mem));
	if (chdir(wd) == -1)
		write_error(cmd, "permission denied", fd);
	else
	{
		tmp->data = ft_strjoin("\033[92mSUCCESS: ", cmd);
		tmp->data = ft_strjoin_nf(tmp->data, ": \n\033[0m", 1);
		tmp->data = ft_strjoin_nf(tmp->data, wd, 1);
		tmp->data = ft_strjoin_nf(tmp->data, "\n", 1);
		tmp->len = ft_strlen(tmp->data);
		write_fd(fd, tmp);
		ft_free_mem(tmp);
	}
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
		ft_chdir(wd, "cd", socket);
	else if (tabl[1][0] != '.' && tabl[1][0] != '/')
	{
		curwd = ft_strjoin_nf(curwd, "/", 1);
		curwd = ft_strjoin_nf(curwd, tabl[1], 1);
		ft_chdir(curwd, "cd", socket);
	}
	else
	{
		newwd = parse_wd(curwd, tabl[1]);
		if (check_if_contains(wd, newwd))
			ft_chdir(newwd, "cd", socket);
		else
			write_error("cd", "permission denied", socket);
	}
	ft_strdel(&curwd);
	ft_free_tabl(tabl);
	return (0);
}

int		exec_lcd(t_mem *mem, char *wd)
{
	char	**tabl;
	char	*curwd;

	tabl = ft_strsplit(mem->data, ' ');
	curwd = NULL;
	curwd = getcwd(curwd, 0);
	if (!tabl[1])
		ft_chdir(wd, "lcd", 1);
	else if (tabl[1][0] != '.' && tabl[1][0] != '/')
	{
		curwd = ft_strjoin_nf(curwd, "/", 1);
		curwd = ft_strjoin_nf(curwd, tabl[1], 1);
		ft_chdir(curwd, "lcd", 1);
	}
	else if (tabl[1][0] == '.' || tabl[1][0] == '/')
		ft_chdir(tabl[1], "lcd", 1);
	else
		ft_chdir(parse_wd(curwd, tabl[1]), "lcd", 1);
	ft_strdel(&curwd);
	ft_free_tabl(tabl);
	return (0);
}
