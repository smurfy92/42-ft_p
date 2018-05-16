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

char *remove_last_dir(char *wd)
{
	int i;
	char  *ret;

	ret = NULL;
	printf("before wd -> %s\n", wd);
	i = ft_strlen(wd);
	while (wd[i] != '/')
	{
		ft_putchar(wd[i]);
		i--;
	}
	printf("ici\n");
	ret = ft_strnew(i);
	ft_memcpy(ret, wd, i);
	printf("before re -> %s\n", ret);
	return (ret);

}

char *parse_wd(char *wd, char *buf)
{
	char  **tabl;
	int 	i;

	i = -1;
	tabl = ft_strsplit(buf, '/');
	while (tabl[++i])
	{
		if (ft_strequ(tabl[i], "..") == 1)
			wd = remove_last_dir(wd);
		else {
			wd = ft_strjoin(wd, "/");
			wd = ft_strjoin(wd, tabl[i]);
		}
	}
	return (wd);
}

int check_if_contains(char *wd, char *newwd)
{
	int i;

	i = -1;

	while (wd[++i])
	{
		if (wd[i] != newwd[i])
			return (0);
	}
	return (1);
}

int		exec_cd(t_mem *mem, char *wd, int socket)
{
	char **tabl;
	char *newwd;
	char *curwd;

	tabl = ft_strsplit(mem->data, ' ');
	curwd = NULL;
	curwd = getcwd(curwd, 0);
	printf("ici start\n");
	if (!tabl[1]){
		printf("ici home\n");
		chdir(wd);

	} else if (tabl[1][0] != '.'){
		chdir(tabl[1]);
	} else{
		printf("ici start parsing\n");
		newwd = parse_wd(curwd, tabl[1]);
		printf("ici wd -> %s\n", wd);
		printf("ici newwd -> %s\n", newwd);
		if (check_if_contains(wd, newwd))
		{
			printf("newwd -> %s \n", newwd);
			chdir(newwd);
		}
	}

	write(socket, "", 1);
	return (0);
}
