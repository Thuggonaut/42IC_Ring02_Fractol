#include "../inc/fractol.h"

double map(t_map_coords coords)
{
	return ((coords.new_max - coords.new_min) *
			(coords.unscaled_num - coords.old_min) /
			(coords.old_max - coords.old_min) + coords.new_min);
}

t_fractol   square_complex(t_fractol z)
{
	t_fractol   result;

	result.cmplx_r = (z.cmplx_r * z.cmplx_r) - (z.cmplx_i * z.cmplx_i);
	result.cmplx_i = 2 * z.cmplx_r * z.cmplx_i;
	return (result);
}

t_fractol   sum_complex(t_fractol z1, t_fractol z2)
{
	t_fractol   result;

	result.cmplx_r = z1.cmplx_r + z2.cmplx_r;
	result.cmplx_i = z1.cmplx_i + z2.cmplx_i;
	return (result);
}

double	atod(char *s)
{
	long	integral;
	double	fractional;
	double	power;
	int		sign;

	integral = 0;
	fractional = 0;
	sign = 1;
	power = 1;
	while (*s == ' ' || (*s >= '\t' && *s <= '\n'))
		++s;
	while (*s == '+' || *s == '-')
		if (*s++ == '-') 
			sign = -sign;
	while (*s != '.' && *s)
		integral = (integral * 10) + (*s++ - '0');
	if (*s == '.')
		++s;
	while (*s)
	{
		power /= 10;
		fractional = fractional + (*s++ - '0') * power;
	}
	return ((integral + fractional) * sign);
}

void	malloc_error(void)
{
	perror("MALLOC ERROR: ");
	exit(EXIT_FAILURE);
}