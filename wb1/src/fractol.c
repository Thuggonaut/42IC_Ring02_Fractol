#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractol	fract;
	
	//Handle arguments
	//Argv must be one of the fractal sets
	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", ft_strlen("mandelbrot") + 1))
		|| (argc == 4 && !ft_strncmp(argv[1], "julia", ft_strlen("julia") + 1)))
	{
		fract.title = argv[1]; //The title of the fractal set will appear on the window
	
		//Init program
		fractol_init(&fract);
		fractol_render(&fract);

		//Put the program in a loop or it'll "finish" executing
		mlx_loop(fract.mlx_connect); //Waiting for events
	}
	else
	{
		//Print msg prompt, free memory and clean exit
		ft_printf("Custom Error Msg\n");
		exit(EXIT_FAILURE);
	}



}