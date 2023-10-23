/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <tquemato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:14:45 by tquemato          #+#    #+#             */
/*   Updated: 2023/10/21 16:03:51 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

static void	events_init(t_fractol *fract)
{
	mlx_hook(fract->window,
		2,
		0,
		handle_key,
		fract);
	mlx_hook(fract->window,
		4,
		0,
		handle_mouse,
		fract);
	mlx_hook(fract->window,
		17,
		0,
		clean_exit,
		fract);
}

static void	data_init(t_fractol *fract)
{
	fract->hypotenuse = 4; //The "hypotenuse" is used to determine if a point has escaped (left the Mandelbrot set) during iteration. Setting it to 4, corresponds to a radius of 2
	fract->iterations = 100; //Arbitrary value that determines how many iterations are performed. A higher number of iterations can provide more detail but requires more computation
	fract->shift_r = 0.0; //Represent shifts (translations) in the real and imaginary components of the complex plane, starting with the default center of the fractal set
	fract->shift_i = 0.0; //They allow you to change the center of the portion of the fractal set that is being rendered
	fract->zoom = 1.0; //Setting 1.0 at the beginning provides a standard reference point, indicating a 1:1 mapping between pixels and complex plane coordinates, that can be increased to zoom in and decreased to zoom out 
}

static void	create_window(t_fractol *fract)
{
	fract->window = mlx_new_window(fract->mlx_connect,
			WIDTH, HEIGHT,
			fract->title);
	if (!fract->window)
	{
		mlx_destroy_window(fract->mlx_connect, fract->window);
		free(fract->mlx_connect);
		malloc_error();
	}
}

static void	create_image(t_fractol *fract)
{
	fract->img = mlx_new_image(fract->mlx_connect, WIDTH, HEIGHT);
	if (!fract->img)
	{
		mlx_destroy_image(fract->mlx_connect, fract->window);
		mlx_destroy_window(fract->mlx_connect, fract->window);
		free(fract->mlx_connect);
		malloc_error();
	}
	fract->img_buffer = mlx_get_data_addr(fract->img,
			&fract->img_bpp,
			&fract->img_line,
			&fract->img_endian);
}

void	fractol_init(t_fractol *fract)
{
	fract->mlx_connect = mlx_init();
	if (!fract->mlx_connect)
		malloc_error();
	create_window(fract);
	create_image(fract);
	events_init(fract);
	data_init(fract);
	fract->current_colour = WHITE;
}
