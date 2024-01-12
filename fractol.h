/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:20:56 by iboutadg          #+#    #+#             */
/*   Updated: 2024/01/12 23:58:47 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <unistd.h>

# ifndef WIDTH
#  define WIDTH 1600
# endif
# ifndef HEIGHT
#  define HEIGHT 1000
# endif
# ifndef ZOOM
#  define ZOOM 200
# endif

# define UP    65362
# define DOWN  65364
# define LEFT  65361
# define RIGHT 65363
# define MAX_ZOOM 4194304
# define MAX_ITER 40

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}				t_data;

typedef struct s_vars
{
	t_data	img;
	void	*mlx;
	void	*win;
	double	juliax;
	double	juliay;
	long	zoom;
	int		xoff;
	int		yoff;
	int		max_iter;
	char	t;
}			t_vars;

void	select_set(t_vars *v);
void	create_img_julia(t_vars *v);
void	create_img_mandelbrot(t_vars *v);
void	create_img_burning(t_vars *v);
void	create_img_cubic(t_vars *v);
void	put_in_pixel(t_data *img, int x, int y, int c);
int		mousehook(int button, int x, int y, t_vars *v);
int		keyhook(int keycode, t_vars *v);
int		change_color(t_vars *v);
void	shift_color(t_data *img, double i, double j);
int		julia_mouse(int x, int y, t_vars *v);
int		finish(t_vars *v);
int		ft_strncmp(char *s1, char *s2, size_t n);
double	ft_atof(char *s);

#endif //FRACTOL_H
