#include "http.h"
#include "libft.h"

char		*concat(const char *s1, const char *s2)
{
	char			*result;
	size_t			len1;
	size_t			len2;

	len1 = strlen(s1);
	len2 = strlen(s2);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
		return (NULL);
	memset(result, 0, len1 + len2 + 1);
	memcpy(result, s1, len1);
	memcpy(result + len1, s2, len2 + 1);
	return (result);
}

uint8_t		*concat_uint8_t(const uint8_t *s1, const uint8_t *s2)
{
	uint8_t			*result;
	size_t			len1;
	size_t			len2;
	size_t			i;

	i = 0;
	while (s1[i] != '\0')
		++i;
	len1 = i;
	i = 0;
	while (s2[i] != '\0')
		++i;
	len2 = i;
	result = (uint8_t *)malloc(sizeof(uint8_t) * (len1 + len2 + 1));
	if (result == NULL)
		return (NULL);
	memset(result, 0, len1 + len2 + 1);
	memcpy(result, s1, len1);
	memcpy(result + len1, s2, len2 + 1);
	return (result);
}
