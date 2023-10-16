#include "fractol.h"

static void	ft_pixel_put(int x, int y, t_fractol *fract, int rgb)
{
	int		offset;

	offset = (y * fract->img_line + x * (fract->img_bpp / 8));
	*(unsigned int *)(fract->img_buffer + offset) = rgb; 
}

static int blend_colours(int colour1, int colour2, double t) //Define a function that interpolates between two colours
{
	int r = (int)((1 - t) * ((colour1 >> 16) & 0xFF) + t * ((colour2 >> 16) & 0xFF) * 5); // Linear interpolation between colour1 and colour2
	int g = (int)((1 - t) * ((colour1 >> 8) & 0xFF) + t * ((colour2 >> 8) & 0xFF) * 5); //`5` is arbitrary value to determin dominance of colour2
	int b = (int)((1 - t) * (colour1 & 0xFF) + t * (colour2 & 0xFF) * 5);

	r = (int)(r + (255 - r) * t * 1.5);
	g = (int)(g + (255 - g) * t * 0.2);
	b = (int)(b + (255 - b) * t * 4);

	return (r << 16) | (g << 8) | b; // Combine the adjusted colour channels
}

void	colour_shift(t_fractol *fract)
{
	static int colours[] = {WHITE, PASTELPINK, GREEN, BLUE, MAGENTA, LIME, ORANGE, PURPLE, AQUA, PINK, ELECTRIC, LIGHTENING, LAVA, YELLOW};
	static int colour_index = 0; // This should be a static variable to remember the current colour index

	colour_index = (colour_index + 1) % (sizeof(colours) / sizeof(colours[0]));
	fract->current_colour = colours[colour_index];
	fractol_render(fract); // Refresh the image after changing colours
}
	
void get_complex_map(int x, int y, t_fractol *fract)
{
	t_fractol	z;
	t_fractol	c;
	int			i;
	int			rgb;

	i = 0;
	z.cmplx_r = (map((t_map_coords){x, -2, +2, 0, WIDTH}) * fract->zoom) + fract->shift_r; 
	z.cmplx_i = (map((t_map_coords){y, +2, -2, 0, HEIGHT}) * fract->zoom) + fract->shift_i;
	c.cmplx_r = z.cmplx_r;
	c.cmplx_i = z.cmplx_i;
	while (i < fract->iterations) 
	{
		z = sum_complex(square_complex(z), c);
		if ((z.cmplx_r * z.cmplx_r) + (z.cmplx_i * z.cmplx_i) > fract->hypotenuse) 
		{
			rgb = blend_colours(BLACK, fract->current_colour, (double)i / fract->iterations);
			ft_pixel_put(x, y, fract, rgb);
			return ;
		}
		++i;
	}
	ft_pixel_put(x, y, fract, BLACK);
}

void	fractol_render(t_fractol *fract)
{
	int x;
	int y;

	y = -1;
	while (++y < HEIGHT) //Checking the coordinates of our 2D plane
	{
		x = -1;
		while (++x < WIDTH) //Checking the coordinates of our 2D plane
			get_complex_map(x, y, fract);
	}
	mlx_put_image_to_window(fract->mlx_connect,
							fract->window,
							fract->img,
							0, 0); //cmplx_r, cmplx_i
}