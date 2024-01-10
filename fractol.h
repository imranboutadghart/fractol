/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 10:33:06 by iboutadg          #+#    #+#             */
/*   Updated: 2024/01/10 23:57:43 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include "mlx.h"
# include <math.h>
# include <unistd.h>

# ifndef WIDTH
#  define WIDTH 1900
# endif
# ifndef HEIGHT
#  define HEIGHT 1080
# endif
# ifndef ZOOM
#  define ZOOM 200
# endif

# define UP    65362
# define DOWN  65364
# define LEFT  65361
# define RIGHT 65363

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}				t_data;

typedef struct s_mlx_vars
{
	t_data		img;
	void		*mlx;
	void		*win;
	long long	zoom;
	double			juliax;
	double			juliay;
	int			xoff;
	int			yoff;
	char		j;
}			t_mlx_vars;

void	create_img(t_mlx_vars *v);
double	convergence(double x, double y, double a, double b);
void	put_in_pixel(t_data *img, int x, int y, int c);
int		mouse_hook(int button, int x, int y, t_mlx_vars *v);
int		keyhook(int keycode, t_mlx_vars *v);
int		change_color(t_mlx_vars *v);
void	shift_color(t_data *img, double i, double j);
int		finish(t_mlx_vars *v);
int		ft_strncmp(char *s1, char *s2, size_t n);
double		ft_atof(char *s);

#endif //FRACTOL_H
