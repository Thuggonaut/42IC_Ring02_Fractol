#include "fractol.h"

void	malloc_error(void)
{
	perror("MALLOC ERROR: "); //Print an error message followed by a description of the last error that occurred retrieved from the errno variabl
	exit(EXIT_FAILURE);
}