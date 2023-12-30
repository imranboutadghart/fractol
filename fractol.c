/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 03:55:35 by iboutadg          #+#    #+#             */
/*   Updated: 2023/12/30 15:29:25 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	shift_color(t_data *img, double i, double j)
{
	int		color;
	int		red;
	int		green;
	int		blue;
	char	*data;

	data = img->addr + (int)j * img->ll + (int)i * (img->bpp / 8);
	color = *(int *)data;
	red = (color & 0xFF0000) >> 16;
	green = (color & 0xFF00) >> 8;
	blue = (color & 0xFF);
	red = (red + 1) % 255;
	green = (green + 1) % 255;
	blue = (blue + 1) % 255;
	color = (red << 16) + (green << 8) + blue;
	*(int *)data = color;
}

void	change_color(t_data *img)
{
	double	i;
	double	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			shift_color(img, i, j);
			j++;
		}
		i++;
	}
}

int loop_hook(t_mlx_vars *v)
{
	change_color(&(v->img));
	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_mlx_vars	v;

	v.mlx = mlx_init();
	if (!v.mlx)
		return (1);
	v.win = mlx_new_window(v.mlx, WIDTH, HEIGHT, "fractol");
	if (!v.win)
		return (1);
	v.img.img = mlx_new_image(v.mlx, WIDTH, HEIGHT);
	if (!v.img.img)
		return (1);
	v.img.addr = mlx_get_data_addr(v.img.img, &(v.img.bpp), \
				&(v.img.ll), &(v.img.endian));
	create_img(&(v.img), WIDTH / 2, HEIGHT / 2, 2);
	mlx_key_hook(v.win, close, &v);
	mlx_mouse_hook(v.win, mouse_hook, &v);
	mlx_loop_hook(v.mlx, loop_hook, &v);
	mlx_loop(v.mlx);
	return (0);
}
