/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <tquemato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:41:29 by tquemato          #+#    #+#             */
/*   Updated: 2023/10/20 15:51:23 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	instructions(void)
{
	ft_printf("\nWelcome to the fractal exploration!\nSadly, MiniLibX's limited capabilities result in slow rendering 😞\n");
	ft_printf("\nTo move the fractal:	Press keys: W, A, S, D or Left, Right, Up, Down arrows\n");
	ft_printf("To zoom in:		Scroll mouse wheel up\n");
	ft_printf("To zoom out:		Scroll mouse wheel down\n");
	ft_printf("To switch colours:	Press: Space bar\n");
	ft_printf("To increase iterations:	Press key: + (from the number pad)\n");
	ft_printf("To decrease iterations:	Press key: -\n");
	ft_printf("To rotate Julia:	Mouse left or right click\n");
	ft_printf("To quit:		Press key: ESC or click X on window, or ^C on command line\n");
	ft_printf("\nTry: <./fractal julia -0.4 +0.6> or <./fractol julia -0.835 -0.2321>\n");
	ft_printf("\nWARNING: Attempting to resize or maximize the window will lose you to the black abyss!\n");
}

void	malloc_error(void)
{
	perror("MALLOC ERROR: "); //Print an error message followed by a description of the last error that occurred retrieved from the errno variable
	exit(EXIT_FAILURE); //Terminate the program, EXIT_FAILURE is a predefined constant with a value of 1, signalling an error has occured
}

void	zoom_in(t_fractol *fract, double mouse_r, double mouse_i)
{
	double	zoom_factor;

	zoom_factor = 0.95;

	//Adjust the zoom factor and shift to keep the cursor at the same point
	fract->shift_r += (mouse_r - fract->shift_r) * (1 - zoom_factor);
	fract->shift_i += (mouse_i - fract->shift_i) * (1 - zoom_factor);
	fract->zoom *= zoom_factor;
}

void	zoom_out(t_fractol *fract, double mouse_r, double mouse_i)
{
	double	zoom_factor;

	zoom_factor = 1.01;

	//Adjust the zoom factor and shift to keep the cursor at the same point
	fract->shift_r += (mouse_r - fract->shift_r) * (1 - zoom_factor);
	fract->shift_i += (mouse_i - fract->shift_i) * (1 - zoom_factor);
	fract->zoom *= zoom_factor;
}
