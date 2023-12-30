/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 03:55:35 by iboutadg          #+#    #+#             */
/*   Updated: 2023/12/30 12:33:28 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	mlx_put_image_to_window(v.mlx, v.win, v.img.img, 0, 0);
	mlx_key_hook(v.win, close, &v);
	mlx_mouse_hook(v.win, mouse_hook, &v);
	mlx_loop(v.mlx);
	return (0);
}
