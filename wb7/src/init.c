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

static void data_init(t_fractol *fract)
{
    fract->hypotenuse = 4;
    fract->iterations = 100;
    fract->shift_r = 0.0;
    fract->shift_i = 0.0;
    fract->mbox_scale = -1.1;

    // Set an initial zoom level for Mandelbox (adjust this value as needed)
    if (!ft_strncmp(fract->title, "Mandelbox", 9))
    {
        fract->zoom = -2.0; // Adjust this value for the desired initial zoom level (smaller value for more zoomed out)
    }
    else
    {
        fract->zoom = 1.0; // Set the default zoom for other fractals
    }
}



static void	create_window(t_fractol *fract)
{
	fract->window = mlx_new_window(fract->mlx_connect, 
									WIDTH, HEIGHT, 
									fract->title); //Create a window
	if (!fract->window)
	{
		mlx_destroy_display(fract->mlx_connect);
		free(fract->mlx_connect);
		malloc_error();
	}
}

static void	create_image(t_fractol *fract)
{
	fract->img = mlx_new_image(fract->mlx_connect, WIDTH, HEIGHT);
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
}

void	fractol_init(t_fractol *fract)
{
	fract->mlx_connect = mlx_init(); //Access the pointer to the extablised connection
	if (!fract->mlx_connect)
		malloc_error();
	create_window(fract);
	create_image(fract);
	events_init(fract);
	data_init(fract);
	fract->current_colour = WHITE;
}