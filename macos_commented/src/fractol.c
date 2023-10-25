/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <tquemato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:12:08 by tquemato          #+#    #+#             */
/*   Updated: 2023/10/18 20:40:30 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	main(int argc, char **argv) //Define a program that launches and renders a fractal image for exploration
{
	t_fractol	fract; //To store a pointer to the fract structure

	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", ft_strlen("mandelbrot") + 1))
		|| (argc == 4 && !ft_strncmp(argv[1], "julia", ft_strlen("julia") + 1))) //Check for valid inputs
	{
		instructions(); //Print instructions
		argv[1][0] = ft_toupper(argv[1][0]); //Convert the first letter of the second argument input, into an uppercase
		fract.title = argv[1]; //The title of the fractal set to appear on top of the window
		if (!ft_strncmp(fract.title, "Julia", 5)) //If the fractal is Julia
		{
			//Convert the real and imaginary command line inputs into a floating point
			fract.julia_r = atod(argv[2]);
			fract.julia_i = atod(argv[3]);
		}
		fractol_init(&fract); //Initiate the fractal program and the fractal data
		fractol_render(&fract); //Render the image
		mlx_loop(fract.mlx_connect); //Put the program in a state of looping or it'll "finish" executing and be non-interactive
		return (0);
	}
	//Else if the argument inputs are incorrect
	ft_printf("Invalid input\nTry:\n");
	ft_printf("<./fractol mandelbrot> or\n<./fractol julia -0.4 +0.6>");
	ft_printf(" or\n<./fractol julia -0.835 -0.2321>\n");
	exit(EXIT_FAILURE); //Terminate the program, EXIT_FAILURE is a predefined constant with a value of 1, signalling an error has occured
}
