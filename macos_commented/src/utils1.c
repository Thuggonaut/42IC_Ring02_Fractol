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

t_fractol	square_complex(t_fractol z) //Define a function that will return the result of squaring the complex number. See #2
{
	t_fractol	result;

	result.cmplx_r = (z.cmplx_r * z.cmplx_r) - (z.cmplx_i * z.cmplx_i); //Calculate the real component of the squared complex number. It takes the square of the real component of z and subtracts the square of the imaginary component of z
	result.cmplx_i = 2 * z.cmplx_r * z.cmplx_i; //Calculate the imaginary component of the squared complex number. It is twice the product of the real and imaginary components of z
	return (result);
}

t_fractol	sum_complex(t_fractol z1, t_fractol z2) //Define a function that will return the result of adding two complex numbers together
{
	t_fractol	result;

	result.cmplx_r = z1.cmplx_r + z2.cmplx_r; //Calculate the real component of the sum of two complex numbers. It adds the real components of z1 and z2
	result.cmplx_i = z1.cmplx_i + z2.cmplx_i; //Calculate the imaginary component of the sum of two complex numbers. It adds the imaginary components of z1 and z2
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

/*
#1 LINEAR INTERPPOLATION: 

- a method for estimating values within a range based on known values at the endpoints of that range. 
- It's like drawing a straight line between two points on a graph and finding the value of any point along that line.

- In context of our map() function, we have a value `unscaled_num` that we want to map from one range to another:
	- `unscaled_num`: 
		The value we want to map.
	- `old_min and old_max`: 
		The original range where unscaled_num is coming from.
	- `new_min and new_max`: 
		The new range where we want to map unscaled_num.
- The basic idea is to find a linear relationship between these two ranges. 

- The formula for linear interpolation:

	MappedValue = (unscaled_num - old_min) / (old_max - old_min) * (new_max - new_min) + new_min

	(unscaled_num - old_min): 
		- This part calculates where unscaled_num is located within the original range. 
		- It measures how far unscaled_num is from the lower boundary (old_min) of the original range.

	(old_max - old_min): 
		- This represents the full span or width of the original range. 
		- It's the difference between the upper and lower boundaries.

	(new_max - new_min): 
		- This represents the full span or width of the new range. 
		- It's the difference between the upper and lower boundaries of the new range.

	(unscaled_num - old_min) / (old_max - old_min): 
		- This part scales the position of unscaled_num within the original range to a position within the [0, 1] interval. 
		- It essentially tells we what fraction of the original range unscaled_num occupies.

	* (new_max - new_min): 
		- This scales the fraction from the previous step to fit within the new range.

	+ new_min: 
		- This shifts the scaled and stretched fraction to align it with the new range. 
		- It's essentially mapping the fraction back to the new range.

- When we're scaling a map, we want to change the dimensions (size) of the map but maintain the same aspect ratio and linear interpolation helps with this:
		- Horizontal Scaling Ratio (x_ratio): This is calculated as the new width divided by the old width.
		- Vertical Scaling Ratio (y_ratio): This is calculated as the new height divided by the old height.
		- For each point on the map (x, y), we apply linear interpolation to calculate the new coordinates (new_x, new_y) after scaling.
		- Essentially, we're stretching or compressing the map in both horizontal and vertical directions based on the scaling ratios


#2	FORMULA TO SQUARE A COMPLEX NUMBER:

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