/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 03:55:35 by iboutadg          #+#    #+#             */
/*   Updated: 2023/12/29 20:18:30 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	put_in_pixel(t_data *img, int x, int y, int c)
{
	char	*data;
	
	data = img->addr + y * img->ll + x * (img->bpp / 8);
	*(int *)data = c;
}

double	convergence(double x, double y, double a, double b)
{
	int i;
	double tmp;

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
	zoom *= 200;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			put_in_pixel(img, i, j, 0x0 +\
				convergence((i - xoff) / zoom, (j - yoff) / zoom, (i - xoff) / zoom, (j - yoff) / zoom) * 0x00051020);
			j++;
		}
		i++;
	}
}

int	mouse_hook(int button, int x, int y, t_mlx_vars *v)
{
	static int z = 2;
	static int cx = WIDTH / 2;
	static int cy = HEIGHT / 2;

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
		create_img(&(v->img), cx, cy, z);
	mlx_put_image_to_window(v->mlx, v->win, (v->img).img, 0, 0);
	return (0);
}

int	close(int keycode, t_mlx_vars *v)
{
	printf("keycode:%d\n", keycode);
	if (113 != keycode && 65307 != keycode)
		return (0);
	mlx_destroy_window(v->mlx, v->win);
	exit(0);
}

int main(void)
{
	t_mlx_vars	v;

	v.mlx = mlx_init();
	if (!v.mlx)
		return (0);
	v.win = mlx_new_window(v.mlx, WIDTH, HEIGHT, "fractol");
	v.img.img = mlx_new_image(v.mlx, WIDTH, HEIGHT);
	v.img.addr = mlx_get_data_addr(v.img.img, &(v.img.bpp),\
				&(v.img.ll), &(v.img.endian));
	if (!v.win)
		return (0);
	create_img(&(v.img), WIDTH / 2, HEIGHT / 2, 2);
	mlx_put_image_to_window(v.mlx, v.win, v.img.img, 0, 0);
	mlx_key_hook(v.win, close, &v);
	mlx_mouse_hook(v.win, mouse_hook, &v);
	mlx_loop(v.mlx);

	return (0);
}
