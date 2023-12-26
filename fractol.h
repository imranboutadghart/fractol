/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 10:33:06 by iboutadg          #+#    #+#             */
/*   Updated: 2023/12/25 14:56:38 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTARCTOL_H
# define FTARCTOL_H

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
#endif //FRACTOL_H
