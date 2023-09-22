
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

void	*or_exit(void *p, const char *msg)
{
	if (p != NULL)
		return (p);
	printf("Error\n%s\n", msg);
	if (errno != 0 && errno != EAGAIN)
		perror("");
	exit(1);
}
