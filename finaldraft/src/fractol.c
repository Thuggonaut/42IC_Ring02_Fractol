#include "../inc/fractol.h"

int	main(int argc, char **argv)
{
	t_fractol	fract;
	
	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", ft_strlen("mandelbrot") + 1))
		|| (argc == 4 &&!ft_strncmp(argv[1], "julia", ft_strlen("julia") +  1)))
	{
		instructions();
		argv[1][0] = ft_toupper(argv[1][0]);
		fract.title = argv[1];
		if (!ft_strncmp(fract.title, "Julia", 5))
		{
			fract.julia_r = atod(argv[2]);
			fract.julia_i = atod(argv[3]); 
		}
		fractol_init(&fract);
		fractol_render(&fract);
		mlx_loop(fract.mlx_connect);
		return (0);
	}
	ft_printf("Invalid input\n");
	ft_printf("Try:\n<./fractol mandelbrot> or\n<./fractal julia -0.4 +0.6> or\n<./fractol julia -0.835 -0.2321>\n");
	exit(EXIT_FAILURE);
}