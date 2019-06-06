#include "server.h"

/*
** Add the connection into a new process
** If successful, return 1. Otherwise, a 0 is returned to indicate an error.
*/

static int		connection_add(int fd, char *address, uint16_t connect)
{
	int			status;
	pid_t		process;
	t_http		*data;

	data = NULL;
	signal(SIGCHLD, sigchld);
	if ((process = fork()) == 0)
	{
		printf("[%d] %s\n", connect, address);
		if (request(fd, &data, &status) == 1)
			status = response(data, fd);
		printf("[%d] %d %s\n", connect, status, get_reponse_message(status));
		_exit(close(fd));
	}
	close(fd);
	if (process < 0)
		perror("ERROR: Fork");
	strdel(&address);
	return ((process < 0) ? 0 : 1);
}

/*
** Accept the incoming connection
** If successful, return 1. Otherwise, a 0 is returned to indicate an error.
*/

static int		loop(void)
{
	int			fd;
	char		*address;
	uint16_t	connect;

	connect = 0;
	address = NULL;
	while ((fd = socket_accept(g_fd, &address)) > 0)
	{
		if (connection_add(fd, address, connect) == 0)
			return (0);
		++connect;
	}
	if (fd == -1)
	{
		perror("ERROR: Accept");
		exit_server();
	}
	return (1);
}

int				g_fd;

/*
** Start a HTTP server listenning on the port PORT
** If successful, return 0. Otherwise, the program quit with EXIT_FAILURE.
*/

int				main(int argc, char **argv)
{
	char	*address;

	address = NULL;
	if (argc != 1 && argv[1] == NULL)
	{
		printf("Usage: ./server\n");
		exit(EXIT_FAILURE);
	}
	if ((g_fd = socket_int()) == -1)
		exit(EXIT_FAILURE);
	if (socket_bind(g_fd, PORT, &address) == 0)
		exit_server();
	if (listen(g_fd, CONNECTION) == -1)
		exit_server();
	printf("Starting new Server\nAdrress: %s:%d\n", address, PORT);
	strdel(&address);
	signal(SIGINT, sigstop);
	if (loop() == 0)
		exit_server();
	close(g_fd);
	return (0);
}
