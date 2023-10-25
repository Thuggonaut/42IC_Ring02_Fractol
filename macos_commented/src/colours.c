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
# LINER INTERPOLATION AND COLOUR BLENDING:

- Linear interpolation between two colours results in a blending of colours because it calculates intermediate colours by smoothly transitioning 
  from one colour to another. 
- This process creates a gradient or transition effect, which visually appears as a blend of the two original colours.

- Suppose we have two colours, Colour A and Colour B, and we want to blend them together. 
- Each colour can be represented as a combination of its red (R), green (G), and blue (B) components, each ranging from 0 to 255 (or 0 to 1 in 
  normalized form). 
	- Red is represented as (255, 0, 0) in RGB (where 255 is the maximum intensity for the red component), and Blue is (0, 0, 255).
- Linear interpolation is performed independently for each of these colour components (R, G, and B).

- We choose a specific point along the gradient. 
	- Let's say we want to find the colour at the halfway point, t = 0.5.

- For the Red component (R), we calculate it as follows:

	- Intermediate_R = (1 - t) * Red_R + t * Blue_R
	- Intermediate_R = (1 - 0.5) * 255 + 0.5 * 0
	- Intermediate_R = 0.5 * 255
	- Intermediate_R = 127.5

- For the Green and Blue components (G and B), we do the same calculation. 
	- In this case, since we're at the halfway point, the Green and Blue components will also be 127.5.

- So, at t = 0.5, we get the colour (127.5, 127.5, 127.5)
	- which is a shade of gray. It's the halfway point between Red and Blue.

- By changing t from 0 to 1, we can find the colours at various points along the gradient. At t = 0, we get Red, and at t = 1, we get Blue. At all 
  the points in between, we get different shades that smoothly transition from Red to Blue.

- Analogy:
  Think of this process as mixing two paint colours, Red and Blue, on a canvas. 
	- At t = 0, we have a canvas filled with pure Red. 
	- At t = 1, the canvas is covered with pure Blue. 
		- As we increase t from 0 to 1, we start adding Blue to the canvas while gradually reducing the amount of Red. 
		- This creates a smooth transition from Red to Blue. 
	- At t = 0.5, we've mixed an equal amount of Red and Blue, resulting in a shade of purple.


BLENDING CALCULATIONS:

The red and green colour components are typically stored in the most significant bits of the colour values. 
That's why we see bit-shifting operations (>>) to extract these components. In most colour representations, red is in the bits 16-23, and green is in bits 8-15. 
The & 0xFF operation is used to mask out any higher-order bits, leaving only the lower 8 bits that represent the colour component.

The blue colour component is usually stored in the least significant bits of the colour values. Unlike red and green, it doesn't need a bit-shifting operation to 
access it because it's already in the lowest 8 bits of the colour value. 
The & 0xFF operation is applied directly to colour1 and colour2 to extract the blue component.


CYCLING THE COLOUR ARRAY:

If colour_index is 13, and there are 14 elements in the colours array (so (sizeof(colours) / sizeof(colours[0])) equals 14), then:
	colour_index + 1 is 14.
	14 % 14 is 0.
So, after this operation, colour_index will be set to 0, effectively "wrapping around" to the beginning of the colours array. 
This ensures that we cycle through the array of colors, and when we reach the end, we start again from the beginning.
*/