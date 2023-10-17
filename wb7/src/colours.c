#include "fractol.h"

int blend_colours(int colour1, int colour2, double t) //Define a function that interpolates between two colours
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