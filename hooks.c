/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:37:25 by iboutadg          #+#    #+#             */
/*   Updated: 2023/12/30 17:33:29 by iboutadg         ###   ########.fr       */
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
