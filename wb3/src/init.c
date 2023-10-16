#include "fractol.h"

static void	events_init(t_fractol *fract)
{
	mlx_hook(fract->window,
				KeyPress,
				KeyPressMask,
				handle_key,
				fract);
	
	mlx_hook(fract->window,
				ButtonPress,
				ButtonPressMask,
				handle_mouse,
				fract);
	mlx_hook(fract->window,
				DestroyNotify,
				StructureNotifyMask,
				clean_exit,
				fract);
}

void	data_init(t_fractol *fract)
{
	fract->hypotenuse = 4; //Re the Mandelbrot, the "hypotenuse" is used to determine if a point has escaped (left the Mandelbrot set) during iteration. Setting it to 4, corresponds to a radius of 2
	fract->iterations = 50; //Arbitrary value that  determines how many iterations are performed to determine if a point is part of the Mandelbrot set. A higher number of iterations can provide more detail but requires more computation
	fract->shift_r = 0.0; //Represent shifts (translations) in the real and imaginary components of the complex plane, starting with the default center of the Mandelbrot set
	fract->shift_i = 0.0; //They allow you to change the center of the portion of the Mandelbrot set that you're rendering
	fract->zoom = 1.0; //Setting 1.0 at the beginning provides a standard reference point, indicating a 1:1 mapping between pixels and complex plane coordinates, that can be increased to zoom in and decreased to zoom out 
}

void	fractol_init(t_fractol *fract)
{
	fract->mlx_connect = mlx_init(); //Access the pointer to the extablised connection
	if (!fract->mlx_connect)
		malloc_error();
	
	fract->window = mlx_new_window(fract->mlx_connect, 
									WIDTH, 
									HEIGHT, 
									fract->title); //Create a window
	if (!fract->window)
	{
		mlx_destroy_display(fract->mlx_connect);
		free(fract->mlx_connect);
		malloc_error();
	}
	
	fract->img = mlx_new_image(fract->mlx_connect, 
										WIDTH, 
										HEIGHT); //Create an image
	if (!fract->img)
	{
		mlx_destroy_window(fract->mlx_connect, fract->window);
		mlx_destroy_display(fract->mlx_connect);
		free(fract->mlx_connect);
		malloc_error();
	}

	fract->img_buffer = mlx_get_data_addr(fract->img, 
								&fract->img_bpp, 
								&fract->img_line,
								&fract->img_endian); //Return the pointer to the pixels
	
	events_init(fract);
	data_init(fract);
	fract->current_colour = WHITE;
}