#include "libft.h"

void	strdel(char **str)
{
	free(*str);
	str = NULL;
}
