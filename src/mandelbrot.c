#include "fractol.h"

//this function decides whether a (x, y) point converges or not
//(whether to draw it black or a crtain color depending on how quick it diverges)
static double	man_convergence(double x, double y, int max_iter)
{
	int		i;
	double	tmp;
	double	a;
	double	b;

	i = 0;
	a = 0;
	b = 0;
	while (i < max_iter)
	{
		tmp = a;
		a = a * a - (b * b) + x;
		b = 2 * tmp * b + y;
		if (a > 10 || b > 10)
			return (i);
		i++;
	}
	return (0);
}

//this function calls the previous for each point in the window
void	create_img_mandelbrot(t_vars *v)
{
	double	i;
	double	j;
	long	zoom;
	double	xoff;
	double	yoff;

	i = 0;
	zoom = ZOOM * v->zoom;
	xoff = v->xoff;
	yoff = v->yoff;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			//again the hex value here is totally random and could be any value except 
			put_in_pixel(&(v->img), i, j, 0x0 + \
			man_convergence((i - xoff) / zoom, \
			(j - yoff) / zoom, v->max_iter) \
							* 0x00051020);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
}
