#include "fractol.h"

void	data_init(t_fractol *fract)
{
	fract->hypotenuse = 4; //2^2
	fract->iterations = 42; //Arbitrary value
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
	
	fract->img_buffer = mlx_new_image(fract->mlx_connect, 
										WIDTH, 
										HEIGHT); //Create an image
	if (!fract->img_buffer)
	{
		mlx_destroy_window(fract->mlx_connect, fract->window);
		mlx_destroy_display(fract->mlx_connect);
		free(fract->mlx_connect);
		malloc_error();
	}

	fract->img_buffer = mlx_get_data_addr(fract->img_buffer, 
											&fract->img_bpp, 
											&fract->img_line,
											&fract->img_endian); //Return the pointer to the pixels
	
	//events_init(fract); //TODO
	data_init(fract);
	


}