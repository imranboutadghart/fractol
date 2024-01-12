/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:20:47 by iboutadg          #+#    #+#             */
/*   Updated: 2024/01/12 23:22:43 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	burn_convergence(double x, double y, int max_iter)
{
	int		i;
	double	tmp;
	double	a;
	double	b;

	i = 0;
	a = x;
	b = y;
	while (i < max_iter)
	{
		tmp = a;
		a = a * a - b * b + x;
		b = 2 * fabs(tmp * b) + y;
		if (a > 10 || b > 10)
			return (i);
		i++;
	}
	return (0);
}

void	create_img_burning(t_vars *v)
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
			burn_convergence((i - xoff) / zoom, \
			(j - yoff) / zoom, v->max_iter) \
							* 0x00151515);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
}
