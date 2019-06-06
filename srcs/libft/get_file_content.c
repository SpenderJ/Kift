#include "libft.h"
#include <fcntl.h>
#include "http.h"

int			get_file_content(uint64_t *file_size, char *filename)
{
	struct stat	st;

	if (stat(filename, &st) != 0 && (*file_size = 0) == 0)
		return (-1);
	*file_size = st.st_size;
	return (0);
}
