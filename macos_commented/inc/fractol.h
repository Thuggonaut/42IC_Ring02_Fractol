#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-macos/mlx.h"
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include <math.h>

//Window dimensions
# define WIDTH	1000
# define HEIGHT	1000

//Colours
//See /minilibx-macos/mlx_rgb.c for more colours defined
# define BLACK			0x000000
# define WHITE			0xFFFFFF
# define GREEN			0x00FF00 
# define BLUE			0x0000FF 
# define MAGENTA		0xFF00FF 
# define LIME			0xCCFF00 
# define ORANGE			0xFF6600
# define PURPLE			0x9932CC 
# define AQUA			0x33CCCC
# define PINK			0xFF66B2
# define ELECTRIC		0x0066FF
# define LIGHTENING		0x00CCFF
# define LAVA			0xFF3300
# define YELLOW			0xFFFF00 
# define PASTELYELLOW	0xFFFF99
# define PASTELPINK		0xFFB6C1

//Data struct for rendering an image in a window
typedef struct s_fractol
{
	char		*title; //The title that will appear on the window
	void		*mlx_connect; //Store a pointer from the mlx_init() function that establishes a connection to the mlx
	void		*window; //Store a pointer from the mlx_new_window() function
	void		*img; //Store a pointer to an image
	char		*img_buffer; //Store the address of the image data as an array of bytes, where each byte represents a pixel
	int			img_bpp; //Represents the number of bits used to for a single pixel in the image
	int			img_line; //Represents the number of bytes in a single row or line of pixel data in the image
	int			img_endian; //Refers to the byte order in which multi-byte data types (like integers) are stored in memory. Common values are 0 or 1 to indicate little-endian or big-endian
	double		cmplx_r; //Refers to the real component of the complex value
	double		cmplx_i; //Refers to the imaginary component of the complex value
	double		hypotenuse; //A reference to check whether the points of the mandelbrot/julia has escaped
	int			iterations; //Refers to the image quality and rendering speed
	double		shift_r; //Store the horizontal translation in the complex plane, to control the movement of the fractal image left or right
	double		shift_i; //Store the vertical translation in the complex plane, to control the movement of the fractal image up or down
	double		zoom; //Store the zoom level of the fractal image. It determines how much the fractal is magnified or reduced in size
	int			current_colour; //Store the current colour of the fractal
	double		julia_r; //If the fractal type is Julia, store the real component of the Julia constant, which is used in the fractal equation for rendering
	double		julia_i; //If the fractal type is Julia, store the imaginary component of the Julia constant, also used in the fractal equation
}	t_fractol;

//Data struct to scale a map, converting a value from one range to another
typedef struct s_map_coords //Store information needed for mapping a value from one range to another
{
	double		unscaled_num; //An unscaled number we want to map from one range to another. It's the value to transform, e.g. it could be the x or y coordinate of a pixel on your window
	double		new_min; //The minimum and maximum values of the new range we want to map `unscaled_num`, defining the lower and upper boundary of the new range
	double		new_max; //E.g., in fractal rendering, this could represent the minimum and maximum values for the x or y coordinates in the complex plane
	double		old_min; //These fields specify the original range from which `unscaled_num` is coming
	double		old_max; //E.g., in fractal rendering, this could be the range of x or y coordinates on the window
}	t_map_coords;

//Initialization 
void		fractol_init(t_fractol *fract); //Initialize the fractol and all its data

//Render
void		fractol_render(t_fractol *fract); //Set the coordinates of the complex plane and render an image
int			blend_colours(int colour1, int colour2, double t); //Use linear interpolation to blend colours
void		colour_shift(t_fractol *fract); //Switch between fractal colours

//Events handling
int			handle_key(int key, t_fractol *fract); //Handle key events
int			handle_mouse(int button, int x, int y, t_fractol *fract); //Handle mouse events
int			clean_exit(t_fractol *fract); //Handle closing the program sucessfully
void		instructions(void); //Print instructions for exploring fractals

//Utils
double		map(t_map_coords coords); //Scale a map from one range to another
t_fractol	sum_complex(t_fractol z1, t_fractol z2); //Add two complex numbers
t_fractol	square_complex(t_fractol z); //Square a complex number
void		malloc_error(void); //Print error message and exit program
double		atod(char *s); //Convert a char to a floating-point number
void		zoom_in(t_fractol *fract, double mouse_r, double mouse_i); //Zoom in a fractal
void		zoom_out(t_fractol *fract, double mouse_r, double mouse_i); //Zoom out a fractal

#endif
