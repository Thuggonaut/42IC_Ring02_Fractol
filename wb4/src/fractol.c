#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractol	fract;
	
	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", ft_strlen("mandelbrot") + 1))
		|| (argc == 4 && !ft_strncmp(argv[1], "julia", ft_strlen("julia") + 1))) //TODO BONUS
	{
		argv[1][0] = ft_toupper(argv[1][0]);
		fract.title = argv[1];
		//TODO PRINT OPTIONS/INSTRUCTIONS
		fractol_init(&fract);
		fractol_render(&fract);
		mlx_loop(fract.mlx_connect);
	}
	else
	{
		ft_printf("Custom Error Msg\n");
		exit(EXIT_FAILURE);
	}
}