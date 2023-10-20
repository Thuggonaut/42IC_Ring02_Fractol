/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <tquemato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:47:33 by tquemato          #+#    #+#             */
/*   Updated: 2023/10/20 19:23:39 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-macos/mlx.h"
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include <math.h>
//# include <X11/X.h>
//# include <X11/keysym.h> 

# define WIDTH	1000
# define HEIGHT	1000

# define Key_ESC = 27
# define Key_Left = 37
# define Key_Right = 39
# define Key_Up = 38
# define Key_Down = 40
# define Key_plus
# define Key_minus
# define Key_Add = 107
# define Key_Subtract = 109
# define Key_W = 87
# define Key_A = 65
# define Key_S = 83
# define Key_D = 68
# define Key_SPACE = 32
# define Button1
# define Button3
# define Button4
# define Button5

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

typedef struct s_map_coords
{
	double		unscaled_num;
	double		new_min;
	double		new_max;
	double		old_min;
	double		old_max;
}	t_map_coords;

void		fractol_init(t_fractol *fract);

void		fractol_render(t_fractol *fract);
int			blend_colours(int colour1, int colour2, double t);
void		colour_shift(t_fractol *fract);

int			handle_key(int key, t_fractol *fract);
int			handle_mouse(int button, int x, int y, t_fractol *fract);
int			clean_exit(t_fractol *fract);
void		instructions(void);

double		map(t_map_coords coords);
t_fractol	sum_complex(t_fractol z1, t_fractol z2);
t_fractol	square_complex(t_fractol z);
void		malloc_error(void);
double		atod(char *s);

#endif
