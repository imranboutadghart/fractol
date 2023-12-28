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

#include <mlx.h>
#include <math.h>
#include "fractol.h"

void	put_in_pixel(t_data *img, int x, int y, int c)
{
	char	*data;
	
	data = img->addr + y * img->line_length + x * (img->bits_per_pixel / 8);
	*(int *)data = c;
}

int	julia_converge(double x, double y)
{
	int i;
	double resx, resy, tmp;
	double	z2x, z2y, z3x, z3y, z4x, z4y;

	i = 0;
	resx = x;
	resy = y;
	// f(z) = z4 + z3 / (z-1) + z2/(z3+4z2+5) + c
	//   z2 = (x + yi)2 = x2 - y2 + 2xyi
	// z1 * z2 = (x1 + y1i) (x2 + y2i) = x1x2 - y1y2 + (x1y2 + x2y1)i
	while (i < 100)
	{
		z2x = resx * resx - (resy * resy);
		z2y = 2 * resx * resy;
		z3x = resx * z2x - resy * z2y;
		z3y = resx * z2y + z2x * resy;
		z4x = z2x * z2x - (z2y * z2y);
		z4y = 2 * z2x * z2y;
		tmp = resx;
		resx = z4x + 0;
		resy = 0;
		if (resx > 10000 || resy > 10000)
			return (i);
		i++;
	}
	return (0);
}


int	mandlebort_converge(double x, double y)
{
	int i;
	double resx, resy, tmp;

	i = 0;
	resx = 0;
	resy = 0;
	// f(z) = z2 + C
	//z2 = (x + yi)2 = x2 - y2 + 2xyi
	while (i < 100)
	{
		tmp = resx;
		resx = resx * resx - (resy * resy) + x;
		resy = 2 * tmp * resy + y;
		if (resx > 10000 || resy > 10000)
			return (i);
		i++;
	}
	return (0);
}

int main(void)
{	
	void	*mlx, *mlx_window;
	t_data	img;
	double	i, j, xoff, yoff;
	int	w, h, zoom;

	mlx = mlx_init();
	if (!mlx)
		return (0);
	w = 1900;
	h = 1000;
	zoom = 1;
	mlx_window = mlx_new_window(mlx, w, h, "fractol");
	img.img    = mlx_new_image(mlx, w, h);
	img.addr   = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	if (!mlx_window)
		return (0);
	i = 0;
	while (i < w)
	{
		j = 0;
		while (j < h)
		{
			xoff = w / 2;
			yoff = h / 2;
			put_in_pixel(&img, i, j, 0x0 + mandlebort_converge((i - w / 2) / (zoom * 200), (j - h/2) / (zoom * 200)) * 0x00051020);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	mlx_loop(mlx);

	return (0);
}
