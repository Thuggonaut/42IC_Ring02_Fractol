#include "../inc/fractol.h"

void	instructions(void)
{
	ft_printf("\nWelcome to the fractal exploration!\nSadly, MiniLibX's limited");
	ft_printf(" capabilities result in slow rendering 😞\n");
	ft_printf("\nTo move the fractal:	Press keys: W, A, S, D or Left, Right, ");
	ft_printf("Up, Down arrows\nTo zoom in:		Scroll mouse wheel up\n");
	ft_printf("To zoom out:		Scroll mouse wheel down\n");
	ft_printf("To switch colours:	Press: Space bar\n");
	ft_printf("To increase iterations:	Press key: + (from the number pad)\n");
	ft_printf("To decrease iterations:	Press key: -\n");
	ft_printf("To rotate Julia:	Mouse left or right click\n");
	ft_printf("To quit:		Press key: ESC or click X on window, or ^C on command ");
	ft_printf("line\n\nWARNING: Attempting to resize or maximize the window ");
	ft_printf("will lose you to the black abyss!\n");
}

void	malloc_error(void)
{
	perror("MALLOC ERROR: ");
	exit(EXIT_FAILURE);
}

void	zoom_in(t_fractol *fract, double mouse_r, double mouse_i)
{
	double zoomFactor;

	zoomFactor = 0.95;
	fract->shift_r += (mouse_r - fract->shift_r) * \
		(1 - zoomFactor);
	fract->shift_i += (mouse_i - fract->shift_i) * \
		(1 - zoomFactor);
	fract->zoom *= zoomFactor;
}

void	zoom_out(t_fractol *fract, double mouse_r, double mouse_i)
{
	double zoomFactor;

	zoomFactor = 1.01;
	fract->shift_r += (mouse_r - fract->shift_r) * \
		(1 - zoomFactor);
	fract->shift_i += (mouse_i - fract->shift_i) * \
		(1 - zoomFactor);
	fract->zoom *= zoomFactor;	
}