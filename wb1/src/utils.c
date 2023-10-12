#include "fractol.h"

/*
* We scale from [0..799] -> [-2..+2]
*/

double map(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
{
    return ((new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min);
}

/*
 * SUM complex
 *
 * fairly easy is vector addition
*/
t_fractol   sum_complex(t_fractol z1, t_fractol z2)
{
    t_fractol   result;

    result.cmplx_r = z1.cmplx_r + z2.cmplx_r;
    result.cmplx_i = z1.cmplx_i + z2.cmplx_i;
    return (result);
}

/*
FORMULA TO SQUARE A COMPLEX NUMBER:

Given a complex number z with a real component x and an imaginary component y:

    z = x + yi

The square of z^2 is calculated as:

*Note: [i^2 = -1 complex maths]

    z^2 
=   (x + yi)^2
=   (x + yi) * (x + yi)

Apply FOIL (First, Outer, Inner, Last):

=   x^2 + xyi + xyi + (yi)^2
= 	x^2 + 2xyi - y^2
=   (x^2 - y^2) + (2xyi)
*/

t_fractol   square_complex(t_fractol z)
{
    t_fractol   result;
    
    result.cmplx_r = (z.cmplx_r * z.cmplx_r) - (z.cmplx_i * z.cmplx_i);
    result.cmplx_i = 2 * z.cmplx_r * z.cmplx_i;
    return (result);
}
