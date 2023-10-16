#include "fractol.h"

void	malloc_error(void)
{
	perror("MALLOC ERROR: "); //Print an error message followed by a description of the last error that occurred retrieved from the errno variabl
	exit(EXIT_FAILURE);
}

double map(t_map_coords coords)
{
	return ((coords.new_max - coords.new_min) * 
			(coords.unscaled_num - coords.old_min) / 
			(coords.old_max - coords.old_min) + coords.new_min);
}

t_fractol   sum_complex(t_fractol z1, t_fractol z2)
{
	t_fractol   result;

	result.cmplx_r = z1.cmplx_r + z2.cmplx_r;
	result.cmplx_i = z1.cmplx_i + z2.cmplx_i;
	return (result);
}

t_fractol   square_complex(t_fractol z)
{
	t_fractol   result;

	result.cmplx_r = (z.cmplx_r * z.cmplx_r) - (z.cmplx_i * z.cmplx_i);
	result.cmplx_i = 2 * z.cmplx_r * z.cmplx_i;
	return (result);
}

int	clean_exit(t_fractol *fract) //For when ESC is pressed or X is clicked in the window
{
	mlx_destroy_image(fract->mlx_connect, fract->img);
	mlx_destroy_window(fract->mlx_connect, fract->window);
	mlx_destroy_display(fract->mlx_connect);
	free(fract->mlx_connect);
	exit(EXIT_SUCCESS);
}