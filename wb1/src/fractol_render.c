#include "fractol.h"

static void	ft_pixel_put(int x, int y, t_fractol *fract, int rgb)
{
	int		offset;

	offset = (y * fract->img_line + x * (fract->img_bpp / 8)); //Calculate where we want to put our pixel on the plane and colour it
	*(unsigned int *)(fract->img_buffer + offset) = rgb; 
}

/*
MANDELBROT formula:
z = z^2 + c

PYTHAGOREAN THEOREM:
In a right triangle (a triangle with one angle of 90 degrees), the square of the length of the hypotenuse (the side opposite
the right angle) is equal to the sum of the squares of the lengths of the other two sides. 

In a right triangle:

Let "a" and "b" be the lengths of the two shorter sides (the legs).
Let "c" be the length of the hypotenuse.
The theorem states that:

a^2 + b^2 = c^2
*/

void	get_complex_map(int x, int y, t_fractol *fract)
{
	t_fractol	z;
	t_fractol	c;
	int			i;
	int			rgb;

	i = 0; 	//At first iteration

	//Complex coordinates scaled
	z.cmplx_r = map(x, -2, +2, 0, WIDTH);
	z.cmplx_i = map(y, +2, -2, 0, HEIGHT);

	c.cmplx_r = z.cmplx_r;
	c.cmplx_i = z.cmplx_i;

	//The number of iterations for z^2 + c until the mandelbrot/julia point has escaped
	while (i < fract->iterations) 
	{
		z = sum_complex(square_complex(z), c);

		//Check if the value escaped using the Pythagorean theorem, if so, put a pixel of a colour
		//If hypotenuse > 2, we assume the point has escaped
		if ((z.cmplx_r * z.cmplx_r) + (z.cmplx_i * z.cmplx_i) > fract->hypotenuse)
		{
			rgb = map(i, BLACK, WHITE, 0, fract->iterations); //BLACK implies the absense of colour, WHITE implies colour
			ft_pixel_put(x, y, fract, rgb); 
			return ;
		}
		++i;
	}
	ft_pixel_put(x, y, fract, PINK);
}

/*
* We check if a point, is on the mandlebrot/julia or not.
*
* We take all the pixels in the image, row by row, and check if they're in the 
*/

void	fractol_render(t_fractol *fract)
{
	int x;
	int y;

	//Check all the pixels from 0 - 799
	y = -1;
	while (++y < HEIGHT) //Checking the coordinates of our 2D plane
	{
		x = -1;
		while (++x < WIDTH) //Checking the coordinates of our 2D plane
		{
			get_complex_map(x, y, fract);
		}
	}
	mlx_put_image_to_window(fract->mlx_connect,
							fract->window,
							fract->img,
							0, 0); //cmplx_r, cmplx_i
}