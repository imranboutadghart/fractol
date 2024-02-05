/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:21:03 by iboutadg          #+#    #+#             */
/*   Updated: 2024/01/15 01:16:49 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	init(t_vars *v)
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
	v->max_iter = MAX_ITER;
	return (0);
}

static int	parse_two_args(char **av, t_vars *v)
{
	if (ft_strncmp(av[1], "m", 2))
		v->t = 0;
	else if (ft_strncmp(av[1], "j", 2))
	{
		v->t = 1;
		v->juliax = -0.59;
		v->juliay = 0.54;
		v->max_iter = 10;
	}
	else if (ft_strncmp(av[1], "b", 2))
		v->t = 2;
	else if (ft_strncmp(av[1], "c", 2))
		v->t = 3;
	else
		return (1);
	return (0);
}

void	parse_args(int ac, char **av, t_vars *v)
{
	static char	s[] = "Usuage:\n./fractol [m]       (mandelbrot)\
		\n./fractol [b]       (burning ship)\
		\n./fractol [c]       (cubic mandelbrot)\
		\n./fractol [j [x y]] (julia with optional starting coordinates)\n";

	if (2 == ac && !parse_two_args(av, v));
	else if (4 == ac && ft_strncmp(av[1], "j", 2))
	{
		v->t = 1;
		v->juliax = ft_atof(av[2]);
		v->juliay = ft_atof(av[3]);
	}
	else
	{
		write(2, s, sizeof(s) * sizeof(char));
		exit(1);
	}
}

void	select_set(t_vars *v)
{
	if (!v->t)
		return (create_img_mandelbrot(v));
	if (1 == v->t)
		return (create_img_julia(v));
	if (2 == v->t)
		return (create_img_burning(v));
	if (3 == v->t)
		return (create_img_cubic(v));
}

int	main(int ac, char **av)
{
	t_vars	v;

	parse_args(ac, av, &v);
	if (init(&v))
		return (1);
	select_set(&v);
	mlx_key_hook(v.win, keyhook, &v);
	mlx_mouse_hook(v.win, mousehook, &v);
	mlx_loop_hook(v.mlx, change_color, &v);
	mlx_hook(v.win, 17, 0, finish, &v);
	mlx_hook(v.win, 6, 1L << 8, julia_mouse, &v);
	mlx_loop(v.mlx);
}
