/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:20:59 by iboutadg          #+#    #+#             */
/*   Updated: 2024/01/12 23:47:54 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mousehook(int b, int x, int y, t_vars *v)
{
	if (5 == b && MAX_ZOOM - 10 > v->zoom)
	{
		v->xoff += (v->xoff - x);
		v->yoff += (v->yoff - y);
		v->zoom *= 2;
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
	else if (1 == v->t && 1 == b)
	{
		v->juliax = ((double) x - WIDTH / 2) / 400;
		v->juliay = ((double) y - HEIGHT / 2) / 400;
	}
	else
		return (0);
	return (select_set(v), 0);
}

int	keyhook(int key, t_vars *v)
{
	if (65307 == key || 113 == key)
		return (finish(v));
	if (v->zoom < 2)
		return (0);
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
	return (select_set(v), 0);
}

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

int	julia_mouse(int x, int y, t_vars *v)
{
	mousehook(1, x, y, v);
	return (0);
}

int	finish(t_vars *v)
{
	mlx_destroy_window(v->mlx, v->win);
	mlx_destroy_image(v->mlx, (v->img).img);
	exit(0);
	return (0);
}
