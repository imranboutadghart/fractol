/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:37:25 by iboutadg          #+#    #+#             */
/*   Updated: 2023/12/30 12:16:26 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_hook(int button, int x, int y, t_mlx_vars *v)
{
	static int	z = 2;
	static int	cx = WIDTH / 2;
	static int	cy = HEIGHT / 2;

	if (1 == button)
	{
		cx += (cx - x);
		cy += (cy - y);
		z *= 2;
	}
	else if (3 == button && z > 1)
	{
		if (z < 5)
		{
			cx = WIDTH / 2;
			cy = HEIGHT / 2;
		}
		else
		{
			cx -= (cx - x) / 2;
			cy -= (cy - y) / 2;
		}
		z /= 2;
	}
	return (create_img(&(v->img), cx, cy, z), \
	mlx_put_image_to_window(v->mlx, v->win, (v->img).img, 0, 0), 0);
}

int	close(int keycode, t_mlx_vars *v)
{
	if (113 != keycode && 65307 != keycode)
		return (0);
	mlx_destroy_window(v->mlx, v->win);
	mlx_destroy_image(v->mlx, v->img.img);
	exit(0);
}
