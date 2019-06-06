#include "server.h"
#include "response.h"

/*
** Finds the protocol version for the response header.
** Will return the version in an unallocated char *
*/

char	*protocol_version(uint8_t protocol)
{
	if (protocol == 1)
		return ("1.0");
	else if (protocol == 2)
		return ("1.1");
	else
		return ("2.0");
}
