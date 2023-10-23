/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <tquemato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:17:36 by tquemato          #+#    #+#             */
/*   Updated: 2023/10/20 15:48:30 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

double	map(t_map_coords coords) //Define a function that scales a map, mapping each point from the original map to the new map while maintaining the aspect ratio
{
	//a. Calculate the numerator of the linear interpolation. This is the first part of the formula used for mapping a value from one range to another
		//multiplied by:
	//b. Calculate where unscaled_num is located within the original range, measuring how far unscaled_num is from the lower boundary `old_min`
		//divided by:
	//c. The difference between the upper and lower boundaries, then, add the `new_min` to the result completing the linear interpolation
	return ((coords.new_max - coords.new_min) \
			* (coords.unscaled_num - coords.old_min) \
			/ (coords.old_max - coords.old_min) + coords.new_min); 
}

t_fractol	square_complex(t_fractol z) //Define a function that will return the result of squaring the complex number
{
	t_fractol	result;

	result.cmplx_r = (z.cmplx_r * z.cmplx_r) - (z.cmplx_i * z.cmplx_i); //Calculate the real component of the squared complex number. It takes the square of the real component of z and subtracts the square of the imaginary component of z
	result.cmplx_i = 2 * z.cmplx_r * z.cmplx_i; //Calculate the imaginary component of the squared complex number. It is twice the product of the real and imaginary components of z
	return (result);
}

t_fractol	sum_complex(t_fractol z1, t_fractol z2) //Define a function that will return the result of adding two complex numbers together
{
	t_fractol	result;

	result.cmplx_r = z1.cmplx_r + z2.cmplx_r; //Calculates the real component of the sum of two complex numbers. It adds the real components of z1 and z2
	result.cmplx_i = z1.cmplx_i + z2.cmplx_i; //Calculates the imaginary component of the sum of two complex numbers. It adds the imaginary components of z1 and z2
	return (result);
}

double	atod(char *s) //Define a function that takes a string and returns a double (a floating-point number)
{
	long	integral; //To store the integral part of the number, the numbers to the left of the "." e.g. in "123.45", "123" is the integral part
	double	fractional; //To store the fractional part of the number, the numbers to the right of the ".", e.g. in "123.45", ".45" is the fractional part
	double	power; //Used as a power of 10 for the fractional part calculation
	int		sign; //To store the sign of the number (positive or negative)

	integral = 0;
	fractional = 0;
	sign = 1;
	power = 1;
	while (*s == ' ' || (*s >= '\t' && *s <= '\n')) //Skip leading whitespace characters
		++s;
	while (*s == '+' || *s == '-') //Check for a plus or minus sign at the beginning of the string
		if (*s++ == '-') 
			sign = -sign; //Update the sign variable accordingly
	while (*s != '.' && *s) //Loop until a "." is encoutered, or the end of the string is reached
		integral = (integral * 10) + (*s++ - '0'); //Multiply the existing integral part by 10 and add the numeric value of the character in the string to calculate the integer part. It does this by subtracting the ASCII value of '0' (which is 48) from the character to convert it to an integer
	if (*s == '.') //Check if a decimal point ('.') is encountered
		++s; //Advance the string pointer
	while (*s) //Process the fractional part of the number, begining from the digit after the "." until the end of the string
	{
		power /= 10; //Divide the fractional part by the appropriate power of 10 (e.g., 0.1, 0.01, etc.)
		fractional = fractional + (*s++ - '0') * power; //Convert the numeric value of each character to an integer and assign it to `fractional`
	}
	return ((integral + fractional) * sign); //Return the sum of the integral and fractional parts, multiplied by the sign to account for the number's sign
}
