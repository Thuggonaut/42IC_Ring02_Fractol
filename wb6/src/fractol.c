#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractol	fract;
	
	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", ft_strlen("mandelbrot") + 1))
		|| (argc == 4 &&!ft_strncmp(argv[1], "julia", ft_strlen("julia") +  1))) //If the ft_strncmp function returns 0 (the strings are equal), the ! operator negates the result and will convert it to 1, which evaluates to true
	{
		argv[1][0] = ft_toupper(argv[1][0]);
		fract.title = argv[1];
		if (!ft_strncmp(fract.title, "Julia", 5))
		{
			fract.julia_r = atod(argv[2]); //Convert command line arguments into a floating point
			fract.julia_i = atod(argv[3]); 
		}
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