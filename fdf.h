/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 11:11:43 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/08/24 11:11:44 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <fcntl.h>
#include <stdio.h>
# include "get_next_line.h"
# include "mlx.h"

typedef	struct s_vec
{
	int		x;
	int		y;
	int		z;
}				t_vec;

typedef	struct	s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_vec	**map_vec;
	int		rows;
	int		columns;
}				t_fdf;

#endif
