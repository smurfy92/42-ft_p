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

int		exec_ls(char **tabl, int fd);
int		exec_pwd(int fd);
int		exec_get(char **tabl, int fd);

void	print_usage(void);
int		write_error(char *cmd, char *err, int fd);
char	*read_fd(int fd);

#endif
