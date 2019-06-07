#include "api.h"
#include "server.h"
#include <stdlib.h>

int				sendaudio(t_http *request, t_reponse *answer)
{
	t_content	*data;
	const char	*word;
	char		buffer[4096];

	word = NULL;
	while ((data = dequeue(request->content)) != NULL)
	{
		if (data->flag == 1)
		{
			snprintf(buffer, sizeof(buffer), "sox %s -r 16000 %s channels 1",
					data->value, "target.wav");
			system(buffer);
			word = get_string("target.wav");
			system("rm target.wav");
			snprintf(buffer, sizeof(buffer), "rm %s", data->value);
			system(buffer);
		}
		content_free(data);
	}
	answer->reponse = OK;
	answer->protocol = (request == NULL) ? 1 : request->protocol;
	answer->date = get_date();
	answer->content_type = strdup("text/plain");
	answer->protocol ? dprintf(answer->fd, "HTTP/%s ",
			protocol_version(answer->protocol)) : 0;
	answer->reponse ? dprintf(answer->fd, "%d %s\r\n", answer->reponse,
			get_reponse_message(answer->reponse)) : 0;
	dprintf(answer->fd, "Connexion: close\r\n");
	answer->date ? dprintf(answer->fd, "Date: %s\r\n", answer->date) : 0;
	answer->date ? dprintf(answer->fd, "Last-Modified: %s\r\n", answer->date)
		: 0;
	word ? dprintf(answer->fd, "Content-Type: %s\r\n",
			answer->content_type) : 0;
	word ? dprintf(answer->fd, "Content-Length: %lu\r\n",
				(long unsigned int)strlen(word)) : 0;
	dprintf(answer->fd, "\r\n");
	if (!word || !strcmp(word, "") || !strcmp(word, " "))
		write(answer->fd, "\"What up, my glip-glops?\"", 25);
	else
	{
		snprintf(buffer, sizeof(buffer), "echo \"%s\" >> .history.txt", word);
		system(buffer);
		write(answer->fd, word, strlen(word));
	}
	return (OK);
}
