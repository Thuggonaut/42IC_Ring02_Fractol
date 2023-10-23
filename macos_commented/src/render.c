/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <tquemato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:16:13 by tquemato          #+#    #+#             */
/*   Updated: 2023/10/20 15:45:51 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

static void	fractol_set(t_fractol *z, t_fractol *c, t_fractol *fract)
{
	if (!ft_strncmp(fract->title, "Julia", 5))
	{
		c->cmplx_r = fract->julia_r;
		c->cmplx_i = fract->julia_i;
	}
	else
	{
		c->cmplx_r = z->cmplx_r;
		c->cmplx_i = z->cmplx_i;
	}
}

static void	ft_pixel_put(int x, int y, t_fractol *fract, int rgb)
{
	int		offset;

	offset = (y * fract->img_line + x * (fract->img_bpp / 8)); //Calculate where we want to put our pixel on the plane
	*(unsigned int *)(fract->img_buffer + offset) = rgb; //Then colour the pixel
}

static void	get_complex_map(int x, int y, t_fractol *fract)
{
	t_fractol	z;
	t_fractol	c;
	int			i;
	int			rgb;

	i = 0;

	//Set up the initial complex number z based on the coordinates x and y on our rendering plane
	z.cmplx_r = (map((t_map_coords){x, -2, +2, 0, WIDTH}) * fract->zoom) + fract->shift_r; //Map the x coordinate to the range of -2 to +2, scale the map according to zoom value, then place z along the real axis of the complex plane
	z.cmplx_i = (map((t_map_coords){y, +2, -2, 0, HEIGHT}) * fract->zoom) + fract->shift_i;//Map the y coordinate to the range of +2 to -2, scale the map according to zoom value, then place z along the imaginary axis of the complex plane
	fractol_set(&z, &c, fract);
	while (i < fract->iterations) //The number of iterations for z^2 + c until the mandelbrot/julia point has escaped
	{
		z = sum_complex(square_complex(z), c);
		if ((z.cmplx_r * z.cmplx_r) + (z.cmplx_i * z.cmplx_i) > fract->hypotenuse) //Check if the value escaped using the Pythagorean theorem. If hypotenuse > 2 the point has escaped
		{
			rgb = blend_colours(PINK, 
								fract->current_colour, 
								(double)i / fract->iterations); //If so, put a pixel of a colour. BLACK implies the absense of colour and will be what you see in the "background" of the window 
			ft_pixel_put(x, y, fract, rgb);
			return ;
		}
		++i;
	}
	ft_pixel_put(x, y, fract, BLACK);
}

void	fractol_render(t_fractol *fract)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			get_complex_map(x, y, fract);
	}
	mlx_put_image_to_window(fract->mlx_connect,
							fract->window,
							fract->img,
							0, 0);  //cmplx_r, cmplx_i
}
