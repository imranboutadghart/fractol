/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 03:55:35 by iboutadg          #+#    #+#             */
/*   Updated: 2024/01/10 19:24:13 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mlx_initiate(t_mlx_vars *v)
{
	v->mlx = mlx_init();
	if (!v->mlx)
		return (1);
	v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, "fractol");
	if (!v->win)
		return (1);
	v->img.img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
	if (!v->img.img)
	{
		mlx_destroy_window(v->mlx, v->win);
		return (1);
	}
	v->img.addr = mlx_get_data_addr(v->img.img, &(v->img.bpp), \
				&(v->img.ll), &(v->img.endian));
	v->xoff = WIDTH / 2;
	v->yoff = HEIGHT / 2;
	v->zoom = 2;
	return (0);
}

int	main(void)
{
	t_mlx_vars	v;

	if (mlx_initiate(&v))
		return (1);
	create_img(&v);
	mlx_key_hook(v.win, keyhook, &v);
	mlx_mouse_hook(v.win, mouse_hook, &v);
	mlx_loop_hook(v.mlx, change_color, &v);
	mlx_hook(v.win, 17, 0, close, &v);
	mlx_loop(v.mlx);
	return (0);
}
