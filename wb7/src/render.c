#include "fractol.h"

static void mandelbox(t_fractol *z, t_fractol *c, double scale)
{
    // Box folding
    if (z->cmplx_r > 1)
        z->cmplx_r = 2 - z->cmplx_r;
    else if (z->cmplx_r < -1)
        z->cmplx_r = -2 - z->cmplx_r;

    if (z->cmplx_i > 1)
        z->cmplx_i = 2 - z->cmplx_i;
    else if (z->cmplx_i < -1)
        z->cmplx_i = -2 - z->cmplx_i;

    // Calculate magnitude
    double mag = sqrt(z->cmplx_r * z->cmplx_r + z->cmplx_i * z->cmplx_i);

    // Ball folding
    if (mag < 0.5)
    {
        z->cmplx_r *= 4;
        z->cmplx_i *= 4;
    }
    else if (mag >= 0.5 && mag < 1)
    {
        double inv_mag_squared = 1.0 / (mag * mag);
        z->cmplx_r *= inv_mag_squared;
        z->cmplx_i *= inv_mag_squared;
    }

    // Apply the scaling and add c
    z->cmplx_r = scale * (z->cmplx_r + c->cmplx_r);
    z->cmplx_i = scale * (z->cmplx_i + c->cmplx_i);
}

static void	fractol_set(t_fractol *z, t_fractol *c, t_fractol *fract)
{
	if (!ft_strncmp(fract->title, "Julia", 5))
	{
		c->cmplx_r = fract->julia_r;
		c->cmplx_i = fract->julia_i;
	}
	else if (!ft_strncmp(fract->title, "Mandelbox", 9))
	{
		mandelbox(z, c, fract->mbox_scale);
		c->cmplx_r = z->mbox_r;
		c->cmplx_i = z->mbox_i;
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

	offset = (y * fract->img_line + x * (fract->img_bpp / 8));
	*(unsigned int *)(fract->img_buffer + offset) = rgb; 
}
	
static void get_complex_map(int x, int y, t_fractol *fract)
{
	t_fractol	z;
	t_fractol	c;
	int			i;
	int			rgb;

	i = 0;
	z.cmplx_r = (map((t_map_coords){x, -2, +2, 0, WIDTH}) * fract->zoom) + fract->shift_r; 
	z.cmplx_i = (map((t_map_coords){y, +2, -2, 0, HEIGHT}) * fract->zoom) + fract->shift_i;
	fractol_set(&z, &c, fract);
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