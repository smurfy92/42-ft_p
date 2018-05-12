
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 11:57:35 by jtranchi          #+#    #+#             */
/*   Updated: 2018/04/28 13:57:12 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

void		print_usage(void)
{
	ft_putendl("usage : serveur <port>");
	exit(0);
}


int		ft_create_serveur(int port)
{
	int sock;
	struct protoent *p;
	struct sockaddr_in sin;

	p = getprotobyname("tcp");
	if (p == 0)
	{
		ft_putendl("proto error");
		exit(-1);
	}
	sock = socket(PF_INET, SOCK_STREAM, p->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		ft_putendl("bind error\n");
		exit(-1);
	}
	listen(sock, 42);
	return (sock);

}

void  exec_ls(char **tabl, int fd)
{
	int f;

	f = fork();
	if (f == 0) {
		dup2(fd, 1);
		dup2(fd, 2);
		execve("/bin/ls", tabl, NULL);
	}
	wait4(f, 0, 0, NULL);
}

void exec_pwd(int fd)
{
	char *wd;
	char *ret;

	wd = NULL;
	wd = getcwd(wd, 0);
	ret = ft_strjoin(wd, "\n");
	write(fd, ret, ft_strlen(ret));
}

int write_error(char *cmd, char *err, int fd)
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


int exec_get(char **tabl, int fd)
{
	char buf[1025];
	char *tmp;
	int r;
	int file;

	if (!tabl[1]) {
		return (write_error("get", "please specify a file", fd));
	} else {
		file = open(tabl[1], O_RDONLY);
		if (file < 0){
			return (write_error("get", "file doesnt exists", fd));
		}
		tmp = ft_strjoin("data ", tabl[1]);
		tmp = ft_strjoin(tmp, " ");
		while ((r = read(file, buf, 1024))){
			buf[1024] = 0;
			tmp = ft_strjoin_nf(tmp, buf, 1);
			ft_bzero(buf, 1024);
			if (r < 1024)
				break ;
		}
		write(fd, tmp, ft_strlen(tmp));
	}
	return (0);
}

int  check_builtin(char *str, int fd)
{
	char **tabl;

	tabl = ft_strsplit(str, ' ');
	if (ft_strequ(tabl[0], "ls") == 1){
		exec_ls(tabl, fd);
		return (0);
	}
	if (ft_strequ(tabl[0], "pwd") == 1){
		exec_pwd(fd);
		return (0);
	}
	if (ft_strequ(tabl[0], "quit") == 1){
		exit(0);
	}
	if (ft_strequ(tabl[0], "get") == 1){
		return (exec_get(tabl, fd));
	}
	return (-1);
}

int main(int argc, char **argv)
{
	int port;
	int socket;
	int cs;
	struct sockaddr sin;
	unsigned int sizesin;
	char buf[1024];

	char *t;

	t = ft_strdup("");
	if (argc <= 1)
		print_usage();
	port = atoi(argv[1]);
	socket = ft_create_serveur(port);
	while (42)
	{
		cs = accept(socket, &sin, &sizesin);
		printf("accepted -> %d\n", cs);
		int f = fork();
		if (f == 0){
			while (42)
			{
				if (recv(cs, buf, 1024, 0) == 0)
					exit(0);
				printf("cs -> %d buf -> %s\n",cs,buf);
				if (check_builtin(buf, cs) == -1){
					write(cs, "", 1);
				}
				ft_bzero(buf, 1024);
			}
			close(socket);
		}
	}
}