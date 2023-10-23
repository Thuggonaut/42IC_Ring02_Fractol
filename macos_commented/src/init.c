/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <tquemato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:14:45 by tquemato          #+#    #+#             */
/*   Updated: 2023/10/21 16:03:51 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

static void	events_init(t_fractol *fract) //Define a function that initialises hook events
{
	//Function prototype from MiniLibx that takes in as parameters: 
	//a pointer to the mlx_new_window() function, 
	//the event code, the event mask, the event function, and 
	//the pointer to the fractal struct
	mlx_hook(fract->window, 2, 0, handle_key, fract);
	mlx_hook(fract->window, 4,0, handle_mouse, fract);
	mlx_hook(fract->window, 17, 0, clean_exit, fract);
}

static void	data_init(t_fractol *fract) //Define a function that sets the inital data of the fractal strucy
{
	fract->hypotenuse = 4; //The "hypotenuse" is used to determine if a point has escaped (left the Mandelbrot set) during iteration. Setting it to 4, corresponds to a radius of 2
	fract->iterations = 100; //Arbitrary value that determines how many iterations are performed. A higher number of iterations can provide more detail but requires more computation
	fract->shift_r = 0.0; //Represent shifts (translations) in the real and imaginary components of the complex plane, starting with the default center of the fractal set
	fract->shift_i = 0.0; //They allow you to change the center of the portion of the fractal set that is being rendered
	fract->zoom = 1.0; //Setting 1.0 at the beginning provides a standard reference point, indicating a 1:1 mapping between pixels and complex plane coordinates, that can be increased to zoom in and decreased to zoom out 
}

static void	create_window(t_fractol *fract) //Define a function that creates a window
{
	fract->window = mlx_new_window(fract->mlx_connect, WIDTH, HEIGHT, fract->title); //Create the window using the defined width and height, assign its title on the window, and assign the pointer of the new window to the `window` data of the struct
	if (!fract->window) //If window creation is unsuccessful
	{
		mlx_destroy_window(fract->mlx_connect, fract->window); //Close and destroy the window of the program ensuring the window is properly closed before exiting
		free(fract->mlx_connect); //Deallocate memory allocated for the fract->mlx_connect pointer, preventing memory leaks and freeing up resources
		malloc_error(); //Print error message to indicate memory allocation failure, then exit
	}
}

static void	create_image(t_fractol *fract) //Define a function that creates a image
{
	fract->img = mlx_new_image(fract->mlx_connect, WIDTH, HEIGHT); //Create the image using the defined width and height, and assign the pointer of the new image to the `img` data of the struct
	if (!fract->img) //If image creation is unsuccessful
	{
		mlx_destroy_image(fract->mlx_connect, fract->window); //Free the memory associated with the image stored in the fract structure
		mlx_destroy_window(fract->mlx_connect, fract->window); //Close and destroy the window of the program ensuring the window is properly closed before exiting
		free(fract->mlx_connect); //Deallocate memory allocated for the fract->mlx_connect pointer, preventing memory leaks and freeing up resources
		malloc_error(); //Print error message to indicate memory allocation failure, then exit
	}
	//If new image creation is successful
	//Call the MiniLibX function to retrieve information about the new image and updates the relevant data fields of the fractal struct, storing pointers to
	//img_buffer: the address of the image data. It points to the location in memory where the pixel data of the image is stored
	//img_bpp: the number of bits used for a single pixel in the image. The & in front of it is used to get a reference to the variable so that the mlx_get_data_addr function can modify its value
	//img_line: the number of bytes in a single row or line of pixel data in the image
	//img_endian: the byte order in which multi-byte data types (like integers) are stored in memory. Common values are 0 or 1, indicating little-endian or big-endian
	fract->img_buffer = mlx_get_data_addr(fract->img,
			&fract->img_bpp,
			&fract->img_line,
			&fract->img_endian);
}

void	fractol_init(t_fractol *fract) //Define a function that initiates our fractal program by calling the defined functions above
{
	fract->mlx_connect = mlx_init(); //Establish a connection to the mlx and assign its pointer to `mlx_connect` data
	if (!fract->mlx_connect) //If connection is unsucessful
		malloc_error(); //Print error message to indicate memory allocation failure, then exit
	//If conection is established successful
	create_window(fract);
	create_image(fract);
	events_init(fract);
	data_init(fract);
	fract->current_colour = WHITE; //Set the current colour of the fractal at launch
}
