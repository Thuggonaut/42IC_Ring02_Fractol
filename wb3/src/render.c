#include "fractol.h"

static void	ft_pixel_put(int x, int y, t_fractol *fract, int rgb)
{
	int		offset;

	offset = (y * fract->img_line + x * (fract->img_bpp / 8));
	*(unsigned int *)(fract->img_buffer + offset) = rgb; 
}


// Define a color blending function that interpolates between two colors
static int blend_colors(int color1, int color2, double t) 
{
    // Linear interpolation between color1 and color2
    int r = (int)((1 - t) * ((color1 >> 16) & 0xFF) + t * ((color2 >> 16) & 0xFF) * 5);
    int g = (int)((1 - t) * ((color1 >> 8) & 0xFF) + t * ((color2 >> 8) & 0xFF) * 5);
    int b = (int)((1 - t) * (color1 & 0xFF) + t * (color2 & 0xFF) * 5);

    // Increase the intensity or brightness with a larger adjustment factor
    r = (int)(r + (255 - r) * t * 1.5); // Adjust red component with a larger factor (2)
    g = (int)(g + (255 - g) * t * 0.2); // Adjust green component with a larger factor (2)
    b = (int)(b + (255 - b) * t * 4); // Adjust blue component with a larger factor (2)

    return (r << 16) | (g << 8) | b; // Combine the adjusted color channels
}

void	colour_shift(t_fractol *fract)
{
	static int colour_index = 0; // This should be a static variable to remember the current color index
	static int colours[] = {WHITE, PASTELPINK, GREEN, BLUE, MAGENTA, LIME, ORANGE, PURPLE, AQUA, PINK, ELECTRIC, LIGHTENING, LAVA, YELLOW};

	colour_index = (colour_index + 1) % (sizeof(colours) / sizeof(colours[0]));
	fract->current_colour = colours[colour_index];
	fractol_render(fract); // Refresh the image after changing colors
}
	

void get_complex_map(int x, int y, t_fractol *fract)
{
	t_fractol	z;
	t_fractol	c;
	int			i;
	int			rgb;

	i = 0;

	//Set up the initial complex number z based on the coordinates x and y on our rendering plane
	z.cmplx_r = (map(x, -2, +2, 0, WIDTH) * fract->zoom) + fract->shift_r; //Map the x coordinate to the range of -2 to +2, scales the map according to zoom value, then place z along the real axis of the complex plane
	z.cmplx_i = (map(y, +2, -2, 0, HEIGHT) * fract->zoom) + fract->shift_i; ////Map the y coordinate to the range of +2 to -2, scales the map according to zoom value, then place z along the imaginary axis of the complex plane

	c.cmplx_r = z.cmplx_r;
	c.cmplx_i = z.cmplx_i;

	while (i < fract->iterations) 
	{
		z = sum_complex(square_complex(z), c);

    	if ((z.cmplx_r * z.cmplx_r) + (z.cmplx_i * z.cmplx_i) > fract->hypotenuse) 
		{
			rgb = blend_colors(BLACK, fract->current_colour, (double)i / fract->iterations);
        	ft_pixel_put(x, y, fract, rgb);
        	return;
    	}
		++i;
	}
	ft_pixel_put(x, y, fract, BLACK);
}

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