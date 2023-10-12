#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include <math.h>

#define WIDTH	800
#define HEIGHT	800

//Colours
#define BLACK		0x000000 //RGB(0, 0, 0)
#define WHITE		0xFFFFFF //RGB(255, 255, 255)
#define RED			0xFF0000 //RGB(255, 0, 0)
#define GREEN		0x00FF00 //RGB(0, 255, 0)
#define BLUE		0x0000FF //RGB(0, 0, 255)
#define MAGENTA		0xFF00FF //A vibrant magenta
#define LIME		0xCCFF00 //A blinding lime
#define ORANGE		0xFF6600 //A blazing neon orange
#define PURPLE		0x660066 //A deep purple
#define AQUA		0x33CCCC //A bright turquoise
#define PINK		0xFF66B2 //As the name suggests!
#define ELECTRIC	0x0066FF //A radiant blue
#define LAVA		0xFF3300 //A bright, molten red

//Data struct
typedef struct s_fractol
{
	char	*title; //The title that will appear on the window
	void	*mlx_connect; //Store a pointer from the mlx_init() function that establishes a connection to the mlx
	void	*window; //Store a pointer from the mlx_new_window() function
	void	*img; //Store a pointer to an image
	char	*img_buffer; //Store the address of the image data as an array of bytes, where each byte represents a pixel
	int		img_bpp; //Represents the number of bits used to for a single pixel in the image
	int		img_line; //Represents the number of bytes in a single row or line of pixel data in the image
	int		img_endian; //Refers to the byte order in which multi-byte data types (like integers) are stored in memory. Common values are 0 or 1 to indicate little-endian or big-endian
	double	cmplx_r; //Refers to the real component of the complex value
	double	cmplx_i; //Refers to the imaginary component of the complex value
	double	hypotenuse; //A reference to check whether the points of the mandelbrot/julia has escaped
	int		iterations; //Refers to the image quality and rendering speed
}	t_fractol;


//Initialization 
void		fractol_init(t_fractol *fract);
void		malloc_error();
void		data_init(t_fractol *fract);


//Render
void		fractol_render(t_fractol *fract);


//Utils
double 		map(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_fractol   sum_complex(t_fractol z1, t_fractol z2);
t_fractol   square_complex(t_fractol z);

# endif