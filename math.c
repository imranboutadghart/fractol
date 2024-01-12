/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:37:28 by iboutadg          #+#    #+#             */
/*   Updated: 2024/01/12 17:51:09 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_in_pixel(t_data *img, int x, int y, int c)
{
	char	*data;

	data = img->addr + y * img->ll + x * (img->bpp / 8);
	*(int *)data = c;
}

double	burn_convergence(double x, double y, double a, double b)
{
	int		i;
	double	tmp;

	i = 0;
	while (i < 50)
	{
		tmp = x;
		x = x * x - y * y + a;
 		y = 2 * fabs(tmp * y) + b;
		if (x > 4 || y > 4)
			return (i);
		i++;
	}
	return (0);
}

double	man_convergence(double x, double y, double a, double b)
{
	int		i;
	double	tmp;

	i = 0;
	while (i < 50)
	{
		tmp = x;
		x = x * x - (y * y) + a;
		y = 2 * tmp * y + b;
		//x = x * x - y * y + a;
 		//y = 2 * fabs(tmp * y) + b;
		if (x > 1000 || y > 1000)
			return (i);
		i++;
	}
	return (0);
}

void	create_img_julia(t_mlx_vars *v, double (*f)(double, double, double, double), int b)
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
	if (!b)
		while (i < WIDTH)
		{
			j = 0;
			while (j < HEIGHT)
			{
				put_in_pixel(&(v->img), i, j, \
				f((i - xoff) / zoom, (j - yoff) / zoom\
				, v->juliax, v->juliay)\
								* 0x00051020);
				j++;
			}
			i++;
		}
	else
		while (i < WIDTH)
		{
			j = 0;
			while (j < HEIGHT)
			{
				put_in_pixel(&(v->img), i, j, 0x0 + \
				f((i - xoff) / zoom, (j - yoff) / zoom\
				, (i - xoff) / zoom, (j - yoff) / zoom)\
								* 0x00051020);
				j++;
			}
			i++;
		}

}

void	create_img(t_mlx_vars *v)
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
	if (v->j == 1)
		return (create_img_julia(v, man_convergence, 0));
	else if (v->j == 2)
		return (create_img_julia(v, burn_convergence, 1));
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			put_in_pixel(&(v->img), i, j, 0x0 + \
			man_convergence((i - xoff) / zoom, (j - yoff) / zoom\
			, (i - xoff) / zoom, (j - yoff) / zoom)\
							* 0x00051020);
			j++;
		}
		i++;
	}
}

void	shift_color(t_data *img, double i, double j)
{
	int		color;
	int		red;
	int		green;
	int		blue;
	char	*data;

	data = img->addr + (int)j * img->ll + (int)i * (img->bpp / 8);
	color = *(int *)data;
	if (0x0 == color)
		return ;
	red = (color & 0xFF0000) >> 16;
	green = (color & 0xFF00) >> 8;
	blue = (color & 0xFF);
	red = (red + 1) % 200;
	green = (green + 2) % 220;
	blue = (blue + 3) % 240;
	color = (red << 16) + (green << 8) + blue;
	*(int *)data = color;
}
