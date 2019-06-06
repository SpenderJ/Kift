#include "server.h"
#include "response.h"

/*
** Function to write the content to the fd of the socket in case of
** succesful connection
*/

static void			write_connection_success(t_reponse *answer)
{
	int		size;
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
	while ((size = read(answer->file_fd, buff, PAGE_SIZE)) > 0)
		write(answer->fd, buff, size);
}

/*
** Handling succesful responses and closing the connection
** In case of error, will link the connection success to the connection error
** function.
** Return the success status implemented
*/

int					end_connection_success(t_http *request, int reponse,
		int fd, t_reponse *answer)
{
	answer->reponse = reponse;
	answer->protocol = (request == NULL) ? 1 : request->protocol;
	answer->fd = fd;
	ft_free(answer->complete_path);
	if (((answer->complete_path = concat(WEBSITE_FOLDER_PATH, request->path))
				== NULL) || (answer->date = get_date()) == NULL)
		return (end_connection_error(request, IER, fd, answer));
	if (!request->path || request->path[0] == '\0' || strcmp(request->path, "/")
			== 0)
		if ((ft_free(answer->complete_path) == 0)
				&& (answer->complete_path = concat(WEBSITE_FOLDER_PATH,
						"/index.html")) == NULL)
			return (end_connection_error(request, IER, fd, answer));
	if (((answer->file_fd = open(answer->complete_path, O_RDONLY)) < 0)
			|| ((get_file_content(&answer->file_size, answer->complete_path))
				< 0))
		return (end_connection_error(request, SERVICE_UNAVAILABLE, fd, answer));
	if ((check_content_type(request, answer->complete_path) != 0)
			|| ((answer->content_type = get_content_type(request,
						answer->complete_path)) == NULL))
		return (end_connection_error(request, BAD_REQUEST, fd, answer));
	write_connection_success(answer);
	http_free(request) ? reponse_free(answer) : reponse_free(answer);
	return (reponse);
}
