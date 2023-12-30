/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:37:28 by iboutadg          #+#    #+#             */
/*   Updated: 2023/12/30 12:54:15 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_in_pixel(t_data *img, int x, int y, int c)
{
	char	*data;

	data = img->addr + y * img->ll + x * (img->bpp / 8);
	*(int *)data = c;
}

double	convergence(double x, double y, double a, double b)
{
	int		i;
	double	tmp;

	i = 0;
	while (i < 100)
	{
		tmp = x;
		x = x * x - (y * y) + a;
		y = 2 * tmp * y + b;
		if (x > 100 || y > 100)
			return (i);
		i++;
	}
	return (5.136898447);
}

void	create_img(t_data *img, double xoff, double yoff, int zoom)
{
	double	i;
	double	j;

	i = 0;
	zoom *= ZOOM;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			put_in_pixel(img, i, j, 0x0 + \
				convergence((i - xoff) / zoom, \
				(j - yoff) / zoom, (i - xoff) / zoom, \
				(j - yoff) / zoom) * 0x00051020);
			j++;
		}
		i++;
	}
}
