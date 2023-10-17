#ifndef FRACTOL_H //COPY REPO BEFORE COMMENTING!!!!!!!!!!!!!!!!!!!!!!!!!!!
# define FRACTOL_H

# include "mlx.h"
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include <math.h>
# include <X11/X.h> //X11 functions and data types for graphics and window management
# include <X11/keysym.h> //Used to identify keyboard events. It allows you to map keycodes to more human-readable key symbols (e.g., XK_a for the 'a' key)

#define WIDTH	1000
#define HEIGHT	1000

//Colours
#define BLACK		0x000000
#define WHITE		0xFFFFFF
#define GREEN		0x00FF00 
#define BLUE		0x0000FF 
#define MAGENTA		0xFF00FF 
#define LIME		0xCCFF00 
#define ORANGE		0xFF6600
#define PURPLE		0x9932CC 
#define AQUA		0x33CCCC
#define PINK		0xFF66B2
#define ELECTRIC	0x0066FF
#define LIGHTENING	0x00CCFF
#define LAVA		0xFF3300
#define YELLOW		0xFFFF00 
#define	PASTELPINK	0xFFB6C1

//Data struct for rendering an image in a window
typedef struct s_fractol
{
	char		*title;
	void		*mlx_connect; 
	void		*window;
	void		*img;
	char		*img_buffer;
	int			img_bpp;
	int			img_line;
	int			img_endian;
	double		cmplx_r;
	double		cmplx_i;
	double		hypotenuse; 
	int			iterations;
	double		shift_r;
	double		shift_i;
	double		zoom;
	int			current_colour;
	double		julia_r;
	double		julia_i;	
}	t_fractol;

//Data struct to scale a map
typedef struct s_map_coords
{
	double		unscaled_num;
	double		new_min;
	double		new_max;
	double		old_min;
	double		old_max;
}	t_map_coords;

//Initialization 
void		fractol_init(t_fractol *fract);

//Render
void		fractol_render(t_fractol *fract);
void		colour_shift(t_fractol *fract);

//Events handling
int			handle_key(int keysym, t_fractol *fract);
int			handle_mouse(int button, int x, int y, t_fractol *fract);
//int			julia_track(int x, int y, t_fractol *fract);

//Utils
double		map(t_map_coords coords);
t_fractol   sum_complex(t_fractol z1, t_fractol z2);
t_fractol   square_complex(t_fractol z);
int			clean_exit(t_fractol *fract);
void		malloc_error();
double		atod(char *s);

# endif