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

#include "../includes/ftp.h"

void	print_usage(void)
{
	ft_putendl("usage : <port>");
	exit(0);
}

int		exec_get(char **tabl, int fd)
{
	t_mem	*tmp;
	int		file;
	t_mem	*mem;

	tmp = NULL;
	tmp = (t_mem*)malloc(sizeof(t_mem));
	if (!tabl[1])
	{
		write_error("get", "please specify a file", fd);
	}
	else
	{
		file = open(tabl[1], O_RDONLY);
		if (file < 0)
			return (write_error("get", "file doesnt exists", fd));
		tmp->data = ft_strjoin("data ", tabl[1]);
		tmp->data = ft_strjoin_nf(tmp->data, " ", 1);
		tmp->len = ft_strlen(tmp->data);
		mem = read_fd(file);
		mem = ft_memjoin(tmp, mem);
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

int			check_if_data(t_mem *mem)
{
	char	**tabl;
	int		fd;
	int		i;

	tabl = ft_strsplit(mem->data, ' ');
	if (ft_strequ(tabl[0], "data") == 1 && tabl[1] && tabl[2])
	{
		fd = open(tabl[1], O_RDWR | O_CREAT, 0666);
		i = 4 + 2 + ft_strlen(tabl[1]) - 1;
		while (++i < mem->len)
			write(fd, &mem->data[i], 1);
	}
	else
		return (-1);
	return (0);
}

int		check_put_data(t_mem *mem, int socket)
{
	char	**tabl;
	int		fd;
	int		i;

	tabl = ft_strsplit(mem->data, ' ');
	if (ft_strequ(tabl[0], "data") == 1 && tabl[1] && tabl[2])
	{
		fd = open(tabl[1], O_RDWR | O_CREAT, 0666);
		i = 4 + 2 + ft_strlen(tabl[1]) - 1;
		while (++i < mem->len)
			write(fd, &mem->data[i], 1);
		write(socket, "", 1);
	}
	else
		return (-1);
	return (0);
}
