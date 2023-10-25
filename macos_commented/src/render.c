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

static void	fractol_set(t_fractol *z, t_fractol *c, t_fractol *fract) //Define a function that configures the complex number c based on the type of fractal being rendered. This function helps define the parameters for the iterative calculations in rendering the fractal
{
	if (!ft_strncmp(fract->title, "Julia", 5)) //If it's a Julia set, it copies the Julia constant into c
	{
		c->cmplx_r = fract->julia_r; //Sets the real component on the complex plane copied from the julia_r data
		c->cmplx_i = fract->julia_i; //Sets the imaginary component on the complex plane copied from the julia_i data
	}
	else //If it's a Mandelbrot, it copies the current point in the fractal space z into c
	{
		c->cmplx_r = z->cmplx_r; //Sets the real component on the complex plane copied from the cmplx_r data of the z structure
		c->cmplx_i = z->cmplx_i; //Sets the imaginary component on the complex plane copied from the cmplx_i data of the z structure
	}
}

static void	ft_pixel_put(int x, int y, t_fractol *fract, int rgb) //Define a function that puts a pixel in an image buffer rather than directly on a window as the original mlx_pixel_put() does, and that causes tearing
{
	int		offset; //To be used as a buffer

	offset = (y * fract->img_line + x * (fract->img_bpp / 8)); //Calculate where we want to put our pixel on the plane
	rgb = *(unsigned int *)(fract->img_addr + offset); //Then retrieve the colour data of the pixel at x and y and colour the pixel
}

static void	get_complex_map(int x, int y, t_fractol *fract) //Define a function that retrieves the relevant data from the fractal struct and performs the iterations and colour calculation for rendering fractals
{
	t_fractol	z; //To store the complex number z for the fractal calculation
	t_fractol	c; //To store the complex number c for the fractal calculation
	int			i; //Used as a counter variable to keep track of the number of iterations
	int			rgb; //To store the colour value for the pixel

	i = 0;

	//Set up the initial complex number z based on the coordinates x and y on our rendering plane
	z.cmplx_r = (map((t_map_coords){x, -2, +2, 0, WIDTH}) * fract->zoom) + fract->shift_r; //Map the x coordinate to the range of -2 to +2, scale the map according to zoom value, then place z along the real axis of the complex plane
	z.cmplx_i = (map((t_map_coords){y, +2, -2, 0, HEIGHT}) * fract->zoom) + fract->shift_i;//Map the y coordinate to the range of +2 to -2, scale the map according to zoom value, then place z along the imaginary axis of the complex plane
	fractol_set(&z, &c, fract); //Sets the complex number c based on the fractal type. If it's a Julia set, it uses the Julia constant; otherwise, it uses the original complex number z
	while (i < fract->iterations) //Iterate until the number of iterations reaches the specified limit in fract->iterations, which we have set initially to be 100 iterations (arbitrary value)
	{
		z = sum_complex(square_complex(z), c); //For each iteration, calculate a new value for z by taking the square of the complex number (z = z^2) and adding the constant c
		if ((z.cmplx_r * z.cmplx_r) + (z.cmplx_i * z.cmplx_i) > fract->hypotenuse) //Check if the value escaped using the Pythagorean theorem. If hypotenuse > 2, the point has escaped
		{
			rgb = blend_colours(BLACK, fract->current_colour, (double)i / fract->iterations); //If the point has escaped, it calculates a colour value based on the number of iterations. BLACK implies the absense of colour and will be what you see in the "background" of the window 
			ft_pixel_put(x, y, fract, rgb); //It puts a pixel of a colour in the window at x and y coordinates. This is the colour seen surrounding the fractal image, where the points have escaped the fractal set
			return ;
		}
		++i; //Move to the next iteration
	}
	ft_pixel_put(x, y, fract, BLACK); //If the point has not escaped after the specified number of iterations, it sets the pixel to black (the fractal shape)
}

void	fractol_render(t_fractol *fract) //Define a function that iterates through all the pixels in the image, row by row, and displays it on the window
{
	int	x; //Used to iterate through the columns of the image
	int	y; //Used to iterate through the rows of the image

	y = -1; //Starts at -1 so that it covers from 0 to (HEIGHT - 1)
	while (++y < HEIGHT) //Loop through each row
	{
		x = -1; //Cover from 0 to (WIDTH - 1)
		while (++x < WIDTH) 
			get_complex_map(x, y, fract); //Calculate the colour for the pixel coordinates, and update the image
	}
	mlx_put_image_to_window(fract->mlx_connect, fract->window, fract->img, 0, 0); //After all pixels have been set, display the rendered image (0, 0: cmplx_r, cmplx_i)
}
