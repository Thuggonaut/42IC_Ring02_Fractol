/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <tquemato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:06:25 by tquemato          #+#    #+#             */
/*   Updated: 2023/10/21 17:25:44 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	clean_exit(t_fractol *fract) //Define a function that successfuly exits a program when ESC is pressed or X is clicked in the window
{
	mlx_destroy_image(fract->mlx_connect, fract->img);
	mlx_destroy_window(fract->mlx_connect, fract->window);
	free(fract->mlx_connect);
	exit(EXIT_SUCCESS);
}

int	handle_key(int key, t_fractol *fract)
{
	if (key == 53)
		clean_exit(fract);
	else if (key == 123 || key == 0)
		fract->shift_r += (0.1 * fract->zoom);
	else if (key == 124 || key == 2)
		fract->shift_r -= (0.1 * fract->zoom);
	else if (key == 126 || key == 13)
		fract->shift_i -= (0.1 * fract->zoom);
	else if (key == 125 || key == 1)
		fract->shift_i += (0.1 * fract->zoom);
	else if (key == 69)
		fract->iterations += 30; //Increase iterations by 30 (arbitrary, do bigger or smaller chunks of iterations at a time)
	else if (key == 78)
		fract->iterations -= 30; //Decrease iterations by 30 (arbitrary, do bigger or smaller chunks of iterations at a time)
	else if (key == 49)
		colour_shift(fract);
	fractol_render(fract); //Refresh the image	
	return (0);
}

static int	julia_track(int button, int x, int y, t_fractol *fract)
{
	if (button == 1 || button == 2)
	{
		fract->julia_r = (map((t_map_coords){x, -2, +2, 0, WIDTH}) * fract->zoom) + fract->shift_r;
		fract->julia_i = (map((t_map_coords){y, +2, -2, 0, HEIGHT}) * fract->zoom) + fract->shift_i;
		fractol_render(fract);
	}
	return (0);
}

int	handle_mouse(int button, int x, int y, t_fractol *fract) //Define a function that handles mouse click and scroll events
{
	double	mouse_r;
	double	mouse_i;

	//Calculate the positions of the cursor in the complex plane
	mouse_r = (x - WIDTH / 2) / (0.5 * WIDTH * fract->zoom) + fract->shift_r; 
	mouse_i = (y - HEIGHT / 2) / (0.5 * HEIGHT * fract->zoom) + fract->shift_i;
	if (!ft_strncmp(fract->title, "Julia", 5))
		julia_track(button, x, y, fract);
	if (button == 4)
		zoom_in(fract, mouse_r, mouse_i);
	else if (button == 5)
		zoom_out(fract, mouse_r, mouse_i);
	fractol_render(fract);
	return (0);
}
