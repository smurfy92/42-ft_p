/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:21:22 by jtranchi          #+#    #+#             */
/*   Updated: 2018/05/12 15:21:23 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

# include <sys/socket.h>
# include <netdb.h>
# include <stdio.h>
# include <arpa/inet.h>
# include "../libft/includes/libft.h"
# define BUFFER 1024

typedef struct			s_buf
{
	char				*str;
	int					len;
}						t_buf;

int		exec_ls(char **tabl, int fd);
int		exec_pwd(int fd);
int		exec_get(char **tabl, int fd);

t_buf	*prompt();
void	remove_back(char *str);

void	print_usage(void);
int		write_error(char *cmd, char *err, int fd);
t_buf	*read_fd(int fd);
void	write_fd(int fd, t_buf *buf);

int		ft_create_client(char *addr, int port);
char	*get_address(char *addr);

#endif
