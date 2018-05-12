/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:21:27 by jtranchi          #+#    #+#             */
/*   Updated: 2018/05/12 15:21:27 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <sys/socket.h>
# include <netdb.h>
# include <stdio.h>
# include <arpa/inet.h>
# include "../libft/includes/libft.h"
# define BUFFER 1024

void	prompt(char *buf);
void	print_usage(void);
int		ft_create_client(char *addr, int port);
char	*read_fd(int fd);
char	*get_address(char *addr);

#endif
