#include "fractol.h"

static void	ft_pixel_put(int x, int y, t_fractol *fract, int rgb)
{
	int		offset;

	offset = (y * fract->img_line + x * (fract->img_bpp / 8));
	*(unsigned int *)(fract->img_buffer + offset) = rgb; 
}


void	get_complex_map(int x, int y, t_fractol *fract)
{
	t_fractol	z;
	t_fractol	c;
	int			i;
	int			rgb;

	i = 0;

	z.cmplx_r = map(x, -2, +2, 0, WIDTH);
	z.cmplx_i = map(y, +2, -2, 0, HEIGHT);

	c.cmplx_r = z.cmplx_r;
	c.cmplx_i = z.cmplx_i;

	while (i < fract->iterations) 
	{
		z = sum_complex(square_complex(z), c);

		if ((z.cmplx_r * z.cmplx_r) + (z.cmplx_i * z.cmplx_i) > fract->hypotenuse)
		{
			rgb = map(i, BLACK, WHITE, 0, fract->iterations); 
			ft_pixel_put(x, y, fract, rgb); 
			return ;
		}
		++i;
	}
	ft_pixel_put(x, y, fract, PINK);
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