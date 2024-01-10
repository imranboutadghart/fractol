/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:37:25 by iboutadg          #+#    #+#             */
/*   Updated: 2024/01/10 23:32:34 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_hook(int button, int x, int y, t_mlx_vars *v)
{
	if (5 == button)
	{
		v->xoff += (v->xoff - x);
		v->yoff += (v->yoff - y);
		v->zoom *= 2;
	}
	else if (4 == button && v->zoom > 1)
	{
		v->xoff = (WIDTH / 2) * (v->zoom < 5) + \
			(v->xoff - (v->xoff - x) / 2) * (v->zoom >= 5);
		v->yoff = (HEIGHT / 2) * (v->zoom < 5) + \
			(v->yoff - (v->yoff - y) / 2) * (v->zoom >= 5);
		v->zoom /= 2;
	}
	else
		return (0);
	return (create_img(v), \
	mlx_put_image_to_window(v->mlx, v->win, (v->img).img, 0, 0), 0);
}

int	finish(t_mlx_vars *v)
{
	mlx_destroy_window(v->mlx, v->win);
	mlx_destroy_image(v->mlx, v->img.img);
	exit(0);
	return (0);
}

int	keyhook(int key, t_mlx_vars *v)
{
	if (113 == key || 65307 == key)
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
	return (create_img(v), \
	mlx_put_image_to_window(v->mlx, v->win, (v->img).img, 0, 0), 0);
}

int	change_color(t_mlx_vars *v)
{
	double	i;
	double	j;

	i = 0;
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
