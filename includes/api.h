#ifndef API_H
# define API_H

# include <server.h>

/*
** Here is the file where you are supposed to declare all your apis.
** Don't forget to modify the following int delaring the number of apis
** implemented.
*/

# define API_COUNT 2

/*
** API structure, all your apis must take these arguments. And be declared
** in a .c file corresponding to their url.
** Submodule for APIS nor already implemented. Will be in a next version.
*/

typedef struct		s_api
{
	char			*name;
	int				(*fct) (t_http *request, t_reponse *answer);
}					t_api;

/*
** Declare your functions name here and add the include api.h at the top of
** each one of your apis
**
** EX : int sendaudio(t_http *request, t_reponse *answer);
*/

int					demo(t_http *request, t_reponse *answer);
int					sendaudio(t_http *request, t_reponse *answer);

/*
** You have to modify and add the content in the srcs/response/response.c
*/

const char			*get_string(char *path);

extern t_api		g_api[API_COUNT];

#endif
