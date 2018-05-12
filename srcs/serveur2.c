/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:13:11 by jtranchi          #+#    #+#             */
/*   Updated: 2018/05/12 15:13:12 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"

void	print_usage(void)
{
	ft_putendl("usage : <port>");
	exit(0);
}

int		exec_get(char **tabl, int fd)
{
	char	*tmp;
	int		file;

	if (!tabl[1])
	{
		write_error("get", "please specify a file", fd);
	}
	else
	{
		file = open(tabl[1], O_RDONLY);
		if (file < 0)
			return (write_error("get", "file doesnt exists", fd));
		tmp = ft_strjoin("data ", tabl[1]);
		tmp = ft_strjoin_nf(tmp, " ", 1);
		tmp = ft_strjoin_nf(tmp, read_fd(file), 3);
		write(fd, tmp, ft_strlen(tmp));
	}
	return (0);
}

int		exec_ls(char **tabl, int fd)
{
	int f;

	f = fork();
	if (f == 0)
	{
		dup2(fd, 1);
		dup2(fd, 2);
		execve("/bin/ls", tabl, NULL);
	}
	wait4(f, 0, 0, NULL);
	return (0);
}

int		exec_pwd(int fd)
{
	char *wd;
	char *ret;

	wd = NULL;
	wd = getcwd(wd, 0);
	ret = ft_strjoin(wd, "\n");
	write(fd, ret, ft_strlen(ret));
	return (0);
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
