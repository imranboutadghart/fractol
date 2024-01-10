/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 10:33:06 by iboutadg          #+#    #+#             */
/*   Updated: 2023/12/30 20:50:04 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include "mlx.h"
# include <math.h>

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
	void	*mlx;
	void	*win;
	t_data	img;
	int		xoff;
	int		yoff;
	long	zoom;
}				t_mlx_vars;

void	create_img(t_data *img, double xoff, double yoff, long zoom);
double	convergence(double x, double y, double a, double b);
void	put_in_pixel(t_data *img, int x, int y, int c);
int		mouse_hook(int button, int x, int y, t_mlx_vars *v);
int		keyhook(int keycode, t_mlx_vars *v);
int		change_color(t_mlx_vars *v);
void	shift_color(t_data *img, double i, double j);
int		close(t_mlx_vars *v);

#endif //FRACTOL_H
