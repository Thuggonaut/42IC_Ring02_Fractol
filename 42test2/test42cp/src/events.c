/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <tquemato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:06:25 by tquemato          #+#    #+#             */
/*   Updated: 2023/10/20 15:48:15 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	clean_exit(t_fractol *fract)
{
	mlx_destroy_image(fract->mlx_connect, fract->img);
	mlx_destroy_window(fract->mlx_connect, fract->window);
	mlx_destroy_display(fract->mlx_connect);
	free(fract->mlx_connect);
	exit(EXIT_SUCCESS);
}

int	handle_key(int keysym, t_fractol *fract)
{
	if (keysym == XK_Escape)
		clean_exit(fract);
	else if (keysym == XK_Left || keysym == XK_a)
		fract->shift_r += (0.1 * fract->zoom);
	else if (keysym == XK_Right || keysym == XK_d)
		fract->shift_r -= (0.1 * fract->zoom);
	else if (keysym == XK_Up || keysym == XK_w)
		fract->shift_i -= (0.1 * fract->zoom);
	else if (keysym == XK_Down || keysym == XK_s)
		fract->shift_i += (0.1 * fract->zoom);
	else if (keysym == XK_plus || keysym == XK_KP_Add)
		fract->iterations += 30;
	else if (keysym == XK_minus || keysym == XK_KP_Subtract)
		fract->iterations -= 30;
	else if (keysym == XK_space)
		colour_shift(fract);
	fractol_render(fract);
	return (0);
}

static int	julia_track(int button, int x, int y, t_fractol *fract)
{
	if (button == Button1 || button == Button3)
	{
		fract->julia_r = (map((t_map_coords){x, -2, +2, 0, WIDTH}) * \
						fract->zoom) + fract->shift_r;
		fract->julia_i = (map((t_map_coords){y, +2, -2, 0, HEIGHT}) * \
						fract->zoom) + fract->shift_i;
		fractol_render(fract);
	}
	return (0);
}

int	handle_mouse(int button, int x, int y, t_fractol *fract)
{
	double	mouse_r;
	double	mouse_i;

	mouse_r = (x - WIDTH / 2) / (0.5 * WIDTH * fract->zoom) + \
		fract->shift_r;
	mouse_i = (y - HEIGHT / 2) / (0.5 * HEIGHT * fract->zoom) + \
	fract->shift_i;
	if (!ft_strncmp(fract->title, "Julia", 5))
		julia_track(button, x, y, fract);
	if (button == Button4)
		zoom_in(fract, mouse_r, mouse_i);
	else if (button == Button5)
		zoom_out(fract, mouse_r, mouse_i);
	fractol_render(fract);
	return (0);
}
