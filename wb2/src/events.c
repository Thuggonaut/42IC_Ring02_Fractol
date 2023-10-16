#include "fractol.h"

int	handle_key(int keysym, t_fractol *fract)
{
	if (keysym == XK_Escape)
		clean_exit(fract); 
	else if (keysym == XK_Left || keysym == XK_a)
		fract->shift_r += (0.1 * fract->zoom);
	else if (keysym == XK_Right || keysym == XK_d)
		fract->shift_r -= (0.1 * fract->zoom);
	else if (keysym == XK_Up || keysym == XK_w)
		fract->shift_i -= (0.1 * fract->zoom);
	else if (keysym == XK_Down || keysym == XK_s)
		fract->shift_i += (0.1 * fract->zoom);
	else if (keysym == XK_plus || keysym == XK_KP_Add)
		fract->iterations += 10;
	else if (keysym == XK_minus || keysym == XK_KP_Subtract)
		fract->iterations -= 10; //Decrease iterations by 10	
	fractol_render(fract); //Refresh the image							
	return (0);
}


int handle_mouse(int button, int x, int y, t_fractol *fract)
{
    // Calculate the position of the cursor in the complex plane
    double mouse_r = (x - WIDTH / 2) / (0.5 * WIDTH * fract->zoom) + fract->shift_r;
    double mouse_i = (y - HEIGHT / 2) / (0.5 * HEIGHT * fract->zoom) + fract->shift_i;

    if (button == Button4) // Zoom in
    {
        double zoomFactor = 0.99;

        // Adjust the zoom factor and shift to keep the cursor at the same point
        fract->shift_r += (mouse_r - fract->shift_r) * (1 - zoomFactor);
        fract->shift_i += (mouse_i - fract->shift_i) * (1 - zoomFactor);
        fract->zoom *= zoomFactor;
    }
    else if (button == Button5) // Zoom out
    {
        double zoomFactor = 1.01;

        // Adjust the zoom factor and shift to keep the cursor at the same point
        fract->shift_r += (mouse_r - fract->shift_r) * (1 - zoomFactor);
        fract->shift_i += (mouse_i - fract->shift_i) * (1 - zoomFactor);
        fract->zoom *= zoomFactor;
    }

    fractol_render(fract); // Refresh the image
    return (0);
}







