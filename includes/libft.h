#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# include "queue.h"

void		strdel(char **str);
char		*concat(const char *s1, const char *s2);
uint8_t		*concat_uint8_t(const uint8_t *s1, const uint8_t *s2);
int			get_file_content(uint64_t *file_size, char *filename);

#endif
