/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:21:01 by iboutadg          #+#    #+#             */
/*   Updated: 2024/01/12 23:24:05 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	julia_convergence(double x, double y, t_vars *v)
{
	int		i;
	int		max_iter;
	double	tmp;
	double	a;
	double	b;

	a = v->juliax;
	b = v->juliay;
	i = 0;
	max_iter = v->max_iter;
	while (i < max_iter)
	{
		tmp = x;
		x = x * x - (y * y) + a;
		y = 2 * tmp * y + b;
		if (x > 10 || y > 10)
			return (i);
		i++;
	}
	return (0);
}

void	create_img_julia(t_vars *v)
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
			put_in_pixel(&(v->img), i, j, 0x0 + \
			julia_convergence((i - xoff) / zoom, \
			(j - yoff) / zoom, v) \
							* 0x00051020);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
}
