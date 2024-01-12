/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:21:11 by iboutadg          #+#    #+#             */
/*   Updated: 2024/01/12 23:30:07 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_in_pixel(t_data *img, int x, int y, int c)
{
	char	*data;

	data = img->addr + y * img->ll + x * (img->bpp / 8);
	*(int *)data = c;
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

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] == s2[i]);
}

int	ft_isnum(char c)
{
	return (c <= '9' && c >= '0');
}

double	ft_atof(char *s)
{
	double	res;
	int		sign;
	int		i;

	sign = 1;
	res = 0;
	i = 0;
	if ('+' == *s || '-' == *s)
		if ('-' == *(s++))
			sign = -1;
	while (*s && ft_isnum(*s))
	{
		res = res * 10 + *(s++) - '0';
		if (res > 1000)
			return (sign * res);
	}
	if (*(s++) != '.')
		return (sign * res);
	while (*s && ft_isnum(*s))
	{
		res += (*(s++) - '0') * pow(10, --i);
		if (i <= -10)
			return (sign * res);
	}
	return (res);
}
