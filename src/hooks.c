#include "fractol.h"

//this is the function that creates the zoom effect
//if the zoom is above a certain number it stops because the limits of the computer (in the subject)
//the math behind it is quite compilcated and i am not willing to explain it in comments
//trust me bro
int	mousehook(int b, int x, int y, t_vars *v)
{
	if (5 == b && MAX_ZOOM - 10 > v->zoom)
	{
		v->xoff += (v->xoff - x);
		v->yoff += (v->yoff - y);
		v->zoom *= 2;
		//adding or subtracting from max_iter to gt more details when zoomed in and less when zoomed out
		v->max_iter += 5;
	}
	else if (4 == b && v->zoom > 1)
	{
		v->xoff = (WIDTH / 2) * (v->zoom < 5) + \
			(v->xoff - (v->xoff - x) / 2) * (v->zoom >= 5);
		v->yoff = (HEIGHT / 2) * (v->zoom < 5) + \
			(v->yoff - (v->yoff - y) / 2) * (v->zoom >= 5);
		v->zoom /= 2;
		v->max_iter -= 5;
	}
	//if 1 is passed to this function it changes the values of julia depending on mouse position
	else if (JULIA == v->t && 1 == b)
	{
		v->juliax = ((double) x - WIDTH / 2) / 400;
		v->juliay = ((double) y - HEIGHT / 2) / 400;
	}
	else
		return (0);
	//the reason i call select set is because it automatically calls the function that will draw
	return (select_set(v), 0);
}

int	keyhook(int key, t_vars *v)
{
	if (65307 == key || 113 == key)
		return (finish(v));
	if (v->zoom < 2)
		return (0);
	//dividing the ZOOM by log2 so that you will move depending on the zoom value and not by a constant
	else if (UP == key)
		v->yoff += ZOOM / log2(v->zoom);
	else if (DOWN == key)
		v->yoff -= ZOOM / log2(v->zoom);
	else if (RIGHT == key)
		v->xoff -= ZOOM / log2(v->zoom);
	else if (LEFT == key)
		v->xoff += ZOOM / log2(v->zoom);
	else
		return (0);
	//the reason i call select set is because it automatically calls the function that will draw
	return (select_set(v), 0);
}

//this function calls shift_color() for each pixel in the image
int	change_color(t_vars *v)
{
	double	i;
	double	j;

	i = 0;
	if (2 == v->t)
		return (0);
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			shift_color(&(v->img), i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
	return (0);
}

//this hooks to mouse moving and changes the parameter passed to julia
int	julia_mouse(int x, int y, t_vars *v)
{
	mousehook(1, x, y, v);
	return (0);
}

//this is a cleaner for when exiting the program
int	finish(t_vars *v)
{
	mlx_destroy_window(v->mlx, v->win);
	mlx_destroy_image(v->mlx, (v->img).img);
	mlx_destroy_display(v->mlx);
	free(v->mlx);
	exit(0);
	return (0);
}
