/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 03:55:35 by iboutadg          #+#    #+#             */
/*   Updated: 2024/01/12 16:56:49 by iboutadg         ###   ########.fr       */
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

void	get_args(int ac, char **av, t_mlx_vars *v)
{
	if (2 == ac && ft_strncmp(av[1], "m", 2))
		v->j = 0;
	else if (2 == ac && ft_strncmp(av[1], "b", 2))
		v->j = 2;
	else if (2 == ac && ft_strncmp(av[1], "j", 2))
	{
		v->j = 1;
		v->juliax = 0;
		v->juliay = 0.8;
	}
	else if (4 == ac && ft_strncmp(av[1], "j", 2))
	{
		v->j = 1;
		v->juliax = ft_atof(av[2]);
		v->juliay = ft_atof(av[3]);
	}
	else
	{
		write(2, "Usuage:\n./fractol [m]\n./fractol [j [x y]]\n", 42);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_mlx_vars	v;

	get_args(ac, av, &v);
	if (mlx_initiate(&v))
		return (1);
	create_img(&v);
	mlx_key_hook(v.win, keyhook, &v);
	mlx_mouse_hook(v.win, mouse_hook, &v);
	mlx_loop_hook(v.mlx, change_color, &v);
	mlx_hook(v.win, 17, 0, finish, &v);
	mlx_loop(v.mlx);
	return (0);
}
