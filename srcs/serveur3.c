/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 13:11:42 by jtranchi          #+#    #+#             */
/*   Updated: 2018/05/21 13:11:42 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftp.h"

int		exec_get(char **tabl, int fd)
{
	t_mem	*tmp;
	int		file;
	t_mem	*mem;

	tmp = NULL;
	tmp = (t_mem*)malloc(sizeof(t_mem));
	if (!tabl[1])
		write_error("get", "please specify a file", fd);
	else
	{
		file = open(tabl[1], O_RDONLY);
		if (file < 0)
			return (write_error("get", "file doesnt exists", fd));
		tmp->data = ft_strjoin("data ", tabl[1]);
		tmp->data = ft_strjoin_nf(tmp->data, " ", 1);
		tmp->len = ft_strlen(tmp->data);
		if (tabl[2])
			mem = ft_memjoin(tmp, read_fd(file));
		else
			mem = tmp;
		close(file);
		write_fd(fd, mem);
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

int		exec_mkdir(char **tabl, int fd)
{
	if (!tabl[1])
		return (write_error("mkdir", "missing argument", fd));
	if (mkdir(tabl[1], 0777) == -1)
		return (write_error("mkdir", "error", fd));
	write(fd, "", 1);
	return (0);
}
