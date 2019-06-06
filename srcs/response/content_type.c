#include "server.h"

/*
** Get the last occurence of the passed char from the position i int
** the string sent
*/

static int		get_post_char(char *str, int i, char c, int add)
{
	while (str[--i] != c)
		if (i == 0)
			return (0);
	return (i + add);
}

/*
** If the content type is correctly formated and match the file format, returns
** 0. Otherwise will return an error and provoq a BAD_REQUEST exception
** (error 400)
**
**
** Examples for request->accept :
** [text/html,application/xhtml+xml,application/xml;q=0.9,*\*;q=0.8]
** [audio/webm,audio/ogg,audio/wav,audio\*;q=0.9,application/ogg;q=0.7,video\*
** ;q=0.6,*\*;q=0.5]
**
** \ are to be replaced by / unfortunately cant comment with these.
*/

static int		check_type(char *accepted, char *complete_path,
		char *file_extension)
{
	int		i;
	int		n;
	int		accept_size;

	i = get_post_char(complete_path, strlen(complete_path), '.', 0);
	if ((file_extension = strdup(&complete_path[++i])) == NULL)
		return (-1);
	i = -1;
	n = strlen(accepted);
	while (++i < n)
	{
		while (accepted[i] != '\0' && accepted[i] != ' ')
			accept_size = ++i;
		i = get_post_char(accepted, i, '/', 1);
		if (strncmp(&accepted[i], file_extension, accept_size - i) == 0 &&
			ft_free(accepted) == 0 && ft_free(file_extension) == 0)
			return (0);
		else if (accepted[i] == '*' && ft_free(accepted) == 0 &&
				ft_free(file_extension) == 0)
			return (0);
		i = accept_size;
	}
	ft_free(file_extension);
	ft_free(accepted);
	return (-1);
}

int				check_content_type(t_http *request, char *complete_path)
{
	char		*accepted;
	int			i;
	int			n;
	int			accept_size;

	i = -1;
	n = -1;
	if (!request || !request->accept)
		return (-1);
	if ((accept_size = strlen(request->accept)) <= 0)
		return (-1);
	if ((accepted = malloc(sizeof(char) * (accept_size + 1))) == NULL)
		return (-1);
	while (++i < accept_size)
	{
		if (request->accept[i] != ',' && request->accept[i] != ';')
			accepted[++n] = request->accept[i];
		else if ((accepted[++n] = ' ') == ' ')
			while (i < accept_size && request->accept[i] != '\0'
					&& request->accept[i] != ',')
				++i;
	}
	accepted[++n] = '\0';
	return (check_type(accepted, complete_path, NULL));
}

/*
** Called only if the check was correct
** Will be return an error 500 in case of an allocation error otherwise
** will return the extension found
*/

char			*get_content_type(t_http *request, char *complete_path)
{
	char		*file_extension;
	int			i;
	int			n;

	n = get_post_char(complete_path, strlen(complete_path), '.', 0);
	if ((file_extension = strdup(&complete_path[++n])) == NULL)
		return (NULL);
	i = -1;
	while (strncmp(file_extension, &request->accept[++i],
				strlen(file_extension)) != 0)
		if (request->accept[i] == '*')
			break ;
	free(file_extension);
	request->accept[i] == '*' ? i = 0 : i;
	n = i;
	while (n > 0 && request->accept[n] != ',' && request->accept[n] != ';')
		--n;
	n != 0 ? n += 1 : n;
	while (request->accept[i] != '\0' && request->accept[i] != ','
			&& request->accept[i] != ';')
		++i;
	i != '\0' ? i -= 1 : i;
	return ((file_extension = strndup(&request->accept[n], (i - n + 1))) == NULL
			? NULL : file_extension);
}
