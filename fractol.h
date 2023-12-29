/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 10:33:06 by iboutadg          #+#    #+#             */
/*   Updated: 2023/12/29 20:27:57 by iboutadg         ###   ########.fr       */
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
#  define HEIGHT 1000
# endif

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
}				t_mlx_vars;

typedef struct s_vars
{
	int	xoff;
	int	yoff;
	int	zoom;
}				t_vars;

#endif //FRACTOL_H
