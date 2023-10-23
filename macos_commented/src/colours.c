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

int	blend_colours(int colour1, int colour2, double t) //Define a color blending function that interpolates between two colors
{
	int	r;
	int	g;
	int	b;

	// Linear interpolation between colour1 and colour2
	//`5` is arbitrary value to determin dominance of colour2
	r = (int)((1 - t) * ((colour1 >> 16) & 0xFF) + t * ((colour2 >> 16) & 0xFF) * 5);
	g = (int)((1 - t) * ((colour1 >> 8) & 0xFF) + t * ((colour2 >> 8) & 0xFF) * 5);
	b = (int)((1 - t) * (colour1 & 0xFF) + t * (colour2 & 0xFF) * 5);

	// Increase the intensity or brightness with a larger adjustment factor
	r = (int)(r + (255 - r) * t * 1.5);
	g = (int)(g + (255 - g) * t * 0.2);
	b = (int)(b + (255 - b) * t * 4);
	return ((r << 16) | (g << 8) | b); //Returned the combined adjusted color channels
}

void	colour_shift(t_fractol *fract)
{
	static int	colours[] = {WHITE, PASTELPINK, GREEN, BLUE, MAGENTA, LIME, ORANGE, PURPLE, AQUA, PINK, ELECTRIC, LIGHTENING, LAVA, YELLOW, PASTELYELLOW}; 
	static int	colour_index = 0; //Static variable to remember the current color index

	colour_index = (colour_index + 1) % (sizeof(colours) / sizeof(colours[0]));
	fract->current_colour = colours[colour_index];
	fractol_render(fract); //Refresh the image after changing colors
}
