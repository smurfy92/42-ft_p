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

#ifndef FTP_H
# define FTP_H

# include <sys/socket.h>
# include <netdb.h>
# include <stdio.h>
# include <arpa/inet.h>
# include "../libft/includes/libft.h"
# define BUFFER 1024

typedef struct			s_mem
{
	char				*data;
	int					len;
}						t_mem;

int		exec_ls(char **tabl, int fd);
int		exec_pwd(int fd);
int		exec_get(char **tabl, int fd);

t_mem	*prompt();
void	remove_back(t_mem *mem);

void	print_usage(void);
int		write_error(char *cmd, char *err, int fd);
t_mem	*read_fd(int fd);
void	write_fd(int fd, t_mem *buf);
t_mem	*ft_memjoin(t_mem *dest, t_mem *src);
int		check_if_data(t_mem *mem);

int		ft_create_client(char *addr, int port);
char	*get_address(char *addr);
int		write_error(char *cmd, char *err, int fd);

#endif
