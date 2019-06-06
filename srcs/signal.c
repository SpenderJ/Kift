#include "server.h"

/*
** Exit the server.
*/

void		exit_server(void)
{
	close(g_fd);
	exit(EXIT_FAILURE);
}

/*
** Stop the server when signal SIGINT is send.
*/

void		sigstop(int sig)
{
	(void)sig;
	printf("Stoping Server\n");
	exit(close(g_fd));
}

/*
** Check if any zombie process exist and close it.
*/

void		sigchld(int sig)
{
	int	status;

	(void)sig;
	while (waitpid(-1, &status, WNOHANG) > 0)
		(void)status;
}
