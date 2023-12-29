/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 03:55:35 by iboutadg          #+#    #+#             */
/*   Updated: 2023/12/27 14:35:22 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_in_pixel(t_data *img, int x, int y, int c)
{
	char	*data;
	
	data = img->addr + y * img->line_length + x * (img->bits_per_pixel / 8);
	*(int *)data = c;
}

double	convergence(double x, double y, double a, double b)
{
	int i;
	double resx, resy, tmp;

	i = 0;
	resx = x;
	resy = y;
	// f(z) = z2 + C
	//z2 = (x + yi)2 = x2 - y2 + 2xyi
	while (i < 50)
	{
		tmp = resx;
		resx = resx * resx - (resy * resy) + a;
		resy = 2 * tmp * resy + b;
		if (resx > 1000 || resy > 1000)
			return (i);
		i++;
	}
	return (5.136898447);
}

void	create_img(t_data *img, int w, int h, double xoff, double yoff, int zoom)
{
	double	i;
	double	j;
	
	i = 0;
	while (i < w)
	{
		j = 0;
		while (j < h)
		{
			put_in_pixel(img, i, j, 0x0 + convergence((i - xoff) / (zoom * 200), (j - yoff) / (zoom * 200), (i - w / 2) / (zoom * 200), (j - h/2) / (zoom * 200)) * 0x00051020);
			j++;
		}
		i++;
	}

}

int	mouse_hook()
{
	static int z = 2;
	//mlx_destroy_window(vars->mlx, vars->win);
	//exit(0);
        create_img(&(vars->img), 1900, 1000, 1900.0 / 2, 1000.0 / 2, z++);
	mlx_put_image_to_window(vars->mlx, vars->win, (vars->img).img, 0, 0);
	return (0);
}
int	close(int keycode, t_mlx_vars *vars)
{
	static int z = 2;
	//mlx_destroy_window(vars->mlx, vars->win);
	//exit(0);
        create_img(&(vars->img), 1900, 1000, 1900.0 / 2, 1000.0 / 2, z++);
	mlx_put_image_to_window(vars->mlx, vars->win, (vars->img).img, 0, 0);
	return (0);
}

int main(void)
{
	t_mlx_vars	vars;
	t_vars	myvars;
	double	i, j, xoff, yoff;
	int	w, h, zoom;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (0);
	w = 1900;
	h = 1000;
	zoom = 1;
	vars.win = mlx_new_window(vars.mlx, w, h, "fractol");
	vars.img.img    = mlx_new_image(vars.mlx, w, h);
	vars.img.addr   = mlx_get_data_addr(vars.img.img, &(vars.img.bits_per_pixel), &(vars.img.line_length), &(vars.img.endian));
	if (!vars.win)
		return (0);
	i = 0;
	create_img(&(vars.img), w, h, w / 2, h / 2, 2);/*
	while (i < w)
	{
		j = 0;
		while (j < h)
		{
			xoff = w / 2;
			yoff = h / 2;
			put_in_pixel(&img, i, j, 0x0 + convergence((i - xoff) / (zoom * 200), (j - yoff) / (zoom * 200), (i - w / 2) / (zoom * 200), (j - h/2) / (zoom * 200)) * 0x00051020);
			j++;
		}
		i++;
	}*/
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L << 0, close, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);

	return (0);
}
