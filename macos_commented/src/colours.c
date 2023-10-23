/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <tquemato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:52:44 by tquemato          #+#    #+#             */
/*   Updated: 2023/10/18 20:27:22 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	blend_colours(int colour1, int colour2, double t) //Define a colour blending function that interpolates between two colours
{
	int	r; //To store the red component of the blended colour
	int	g; //To store the green component of the blended colour
	int	b; //To store the blue component of the blended colour

	//For each rgb calculation, it's a linear interpolation between colour1 and colour2
	//`5` is arbitrary value to determin dominance of colour2
	r = (int)((1 - t) * ((colour1 >> 16) & 0xFF) + t * ((colour2 >> 16) & 0xFF) * 5); //Calculate the red component of the blended colour. The >> 16 operation extracts the red component (the most significant 8 bits) from each colour. The & 0xFF operation ensures we only consider the lower 8 bits. The formula calculates the blended red component using t
	g = (int)((1 - t) * ((colour1 >> 8) & 0xFF) + t * ((colour2 >> 8) & 0xFF) * 5); //Similarly, calculate the green component of the blended colour. See #1
	b = (int)((1 - t) * (colour1 & 0xFF) + t * (colour2 & 0xFF) * 5); //Similarly, calculate the blue component of the blended colour

	// Increase the intensity or brightness with a larger adjustment factor
	r = (int)(r + (255 - r) * t * 1.5); //Increase the intensity or brightness of the red component based on the value of t. It adjusts the red component to make it brighter
	g = (int)(g + (255 - g) * t * 0.2); //Similarly, adjust the green component to control its brightness
	b = (int)(b + (255 - b) * t * 4); //Similarly, adjust the blue component to control its brightness
	return ((r << 16) | (g << 8) | b); //Return the combined adjusted colour channels
}

void	colour_shift(t_fractol *fract) //Define a function that cycles through the colour array, setting the current_colour data for the fractal
{
	static int	colours[] = {WHITE, PASTELPINK, GREEN, BLUE, MAGENTA, LIME, ORANGE, PURPLE, AQUA, PINK, ELECTRIC, LIGHTENING, LAVA, YELLOW, PASTELYELLOW}; 
	static int	colour_index = 0; //Static variable to remember the current colour index

	colour_index = (colour_index + 1) % (sizeof(colours) / sizeof(colours[0])); //Update the colour_index by increasing it by 1 and wrap around to 0 if it exceeds the number of elements in the colours array. This is done using the modulo operator %. See #2
	fract->current_colour = colours[colour_index]; //Update the current_colour data of the fractal struct
	fractol_render(fract); //Refresh the image after changing colours
}

/*
BLENDING CALCULATIONS:

The red and green colour components are typically stored in the most significant bits of the colour values. 
That's why you see bit-shifting operations (>>) to extract these components. In most colour representations, red is in the bits 16-23, and green is in bits 8-15. 
The & 0xFF operation is used to mask out any higher-order bits, leaving only the lower 8 bits that represent the colour component.

The blue colour component is usually stored in the least significant bits of the colour values. Unlike red and green, it doesn't need a bit-shifting operation to 
access it because it's already in the lowest 8 bits of the colour value. 
The & 0xFF operation is applied directly to colour1 and colour2 to extract the blue component.


CYCLING THE COLOUR ARRAY:

If colour_index is 13, and there are 14 elements in the colours array (so (sizeof(colours) / sizeof(colours[0])) equals 14), then:
	colour_index + 1 is 14.
	14 % 14 is 0.
So, after this operation, colour_index will be set to 0, effectively "wrapping around" to the beginning of the colours array. 
This ensures that you cycle through the array of colors, and when you reach the end, you start again from the beginning.
*/