#include "server.h"
#include "response.h"

/*
** Function to write the content of the error page linked to the error in
** case of unsuccesful connection
** Return the error response value
*/

static int			write_connection_error(t_reponse *answer)
{
	int		size;
	int		reponse;
	char	buff[PAGE_SIZE];

	answer->protocol ? dprintf(answer->fd, "HTTP/%s ",
			protocol_version(answer->protocol)) : 0;
	answer->reponse ? dprintf(answer->fd, "%d %s\r\n", answer->reponse,
				get_reponse_message(answer->reponse)) : 0;
	dprintf(answer->fd, "Connexion: close\r\n");
	answer->date ? dprintf(answer->fd, "Date: %s\r\n", answer->date) : 0;
	answer->date ? dprintf(answer->fd, "Last-Modified: %s\r\n", answer->date)
		: 0;
	answer->content_type ? dprintf(answer->fd, "Content-Type: %s\r\n",
			answer->content_type) : 0;
	answer->file_size ? dprintf(answer->fd, "Content-Length: %lu\r\n",
				(long unsigned int)answer->file_size) : 0;
	dprintf(answer->fd, "\r\n");
	if (answer->file_fd != -1)
		while ((size = read(answer->file_fd, buff, PAGE_SIZE)) > 0)
			write(answer->fd, buff, size);
	reponse = answer->reponse;
	reponse_free(answer);
	return (reponse);
}

/*
** Handling bad responses closing the connection
** Return the error status implemented
*/

int					end_connection_error(t_http *request, int reponse, int fd,
		t_reponse *answer)
{
	char			str[4];

	answer->reponse = reponse;
	answer->protocol = (request == NULL) ? 1 : request->protocol;
	answer->fd = fd;
	if ((((answer->complete_path = concat(ERROR_FOLDER_PATH, str)) == NULL)
				|| ((answer->complete_path = concat(answer->complete_path,
							".html")) == NULL)) && reponse_free(answer) == 0)
		return (response_error(fd, request, reponse));
	sprintf(str, "%d", reponse);
	if ((((answer->file_fd = open(answer->complete_path, O_RDONLY)) < 0) ||
				((get_file_content(&answer->file_size, answer->complete_path))
				< 0)) && http_free(request) == 1)
		return (write_connection_error(answer));
	if (check_content_type(request, answer->complete_path) != 0
			&& http_free(request) == 1)
		return (write_connection_error(answer));
	if ((((answer->content_type = get_content_type(request,
							answer->complete_path)) == NULL)
				|| ((answer->date = get_date()) == NULL))
			&& http_free(request) == 1)
		return (write_connection_error(answer));
	write_connection_error(answer);
	return (reponse);
}

/*
** Function which can be called by the server to print an error
** Returns the error status implemented
*/

int					response_error(int fd, t_http *request, int reponse)
{
	t_reponse	*answer;

	if (reponse == INTERNAL_SERVER_ERROR || (answer = reponse_init()) == NULL)
	{
		write(fd, "HTTP/1.0 500 Internal Server Error\r\n\r\n", 37);
		close(fd);
		return (INTERNAL_SERVER_ERROR);
	}
	answer->fd = fd;
	answer->reponse = reponse;
	answer->protocol = (request == NULL) ? 1 : request->protocol;
	answer->date = get_date();
	http_free(request);
	return (write_connection_error(answer));
}
