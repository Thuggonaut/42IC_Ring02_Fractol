/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <tquemato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:06:25 by tquemato          #+#    #+#             */
/*   Updated: 2023/10/21 17:25:44 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	clean_exit(t_fractol *fract) //Define a function that successfuly exits a program when ESC is pressed or X is clicked in the window
{
	mlx_destroy_image(fract->mlx_connect, fract->img); //Free the memory associated with the image stored in the fract structure
	mlx_destroy_window(fract->mlx_connect, fract->window); //Close and destroy the window of the program ensuring the window is properly closed before exiting
	free(fract->mlx_connect); //Deallocate memory allocated for the fract->mlx_connect pointer, preventing memory leaks and freeing up resources
	exit(EXIT_SUCCESS); //Terminate the program. EXIT_SUCCESS is a constant indicating a successful program exit - a convention to return 0 from the main function to indicate a successful execution
}

int	handle_key(int key, t_fractol *fract) //Define a function that handles key press events
{
	//Applescript codes are used
	if (key == 53) //If ESC
		clean_exit(fract); //Exit in a clean way
	else if (key == 123 || key == 0) //If left arrow or `A`
		fract->shift_r += (0.1 * fract->zoom); //Shift the image left. `0.1` is arbitrary, the smaller the floating point, the smaller the distance it shifts
	else if (key == 124 || key == 2) //If right arrow or `D`
		fract->shift_r -= (0.1 * fract->zoom); //Shift the image right
	else if (key == 126 || key == 13) //If up arrow or `W`
		fract->shift_i -= (0.1 * fract->zoom); //Shift the image up
	else if (key == 125 || key == 1) //If down arrow or `S`
		fract->shift_i += (0.1 * fract->zoom); //Shift the image down
	else if (key == 69) //If number pad `+`
		fract->iterations += 30; //Increase iterations by 30 (arbitrary, do bigger or smaller chunks of iterations at a time)
	else if (key == 78) //If number pad `-`
		fract->iterations -= 30; //Decrease iterations by 30 (arbitrary, do bigger or smaller chunks of iterations at a time)
	else if (key == 49) //If SPACE
		colour_shift(fract); //Shift fractal colour
	fractol_render(fract); //Refresh the image	
	return (0);
}

static int	julia_track(int button, int x, int y, t_fractol *fract) //Define a function that changes the z complex values, exploring varying patterns of the fractal set. See #1
{
	if (button == 1 || button == 2) //If left or right mouse click
	{
		//Calculate the new value for the real and imaginary components of the Julia constant (julia_r and julia_i)
		//It uses the map function to map the x(real) and y(imaginary) coordinates of the mouse pointer from one range [-2, 2] or [2, -2] to [0, WIDTH] or [0, HEIGHT]
		//It then scales this value by the fract->zoom and adds the horixontal or vertical trranslations
		fract->julia_r = (map((t_map_coords){x, -2, +2, 0, WIDTH}) * fract->zoom) + fract->shift_r; 
		fract->julia_i = (map((t_map_coords){y, +2, -2, 0, HEIGHT}) * fract->zoom) + fract->shift_i;
		fractol_render(fract); //Update and refresh the rendering with the new Julia constant values
	}
	return (0);
}

int	handle_mouse(int button, int x, int y, t_fractol *fract) //Define a function that handles mouse click and scroll events
{
	double	mouse_r; //To store the real component of the cursor's position in the complex plane
	double	mouse_i; //To store the imaginary component of the cursor's position in the complex plane

	//Calculate the positions of the cursor in the complex plane
	//Take into account the current zoom level, the x and y position of the cursor
	//The cursor's position is centered by subtracting half of the screen width or height
	//The result is then scaled by (0.5 * WIDTH/HEIGHT * fract->zoom) and adjusted by the current shift in the real and imaginary components
	mouse_r = (x - WIDTH / 2) / (0.5 * WIDTH * fract->zoom) + fract->shift_r; 
	mouse_i = (y - HEIGHT / 2) / (0.5 * HEIGHT * fract->zoom) + fract->shift_i;
	if (!ft_strncmp(fract->title, "Julia", 5)) //Check if the current fractal type is "Julia"
		julia_track(button, x, y, fract); //Call the julia_track function to use the left and right mouse clicks to change julia positions
	if (button == 4)
		zoom_in(fract, mouse_r, mouse_i);
	else if (button == 5)
		zoom_out(fract, mouse_r, mouse_i);
	fractol_render(fract); //Refresh the image
	return (0);
}