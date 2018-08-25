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
# include "get_next_line.h"
# include "mlx.h"

# define WIDTH 720
# define HEIGHT 480
# define UP_ARROW 126
# define DOWN_ARROW 125
# define LEFT_ARROW 123
# define RIGHT_ARROW 124

typedef	struct s_vec
{
	int		x;
	int		y;
	int		z;
	int		color;
}				t_vec;

typedef	struct	s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_vec	**map_vec;
	int		rows;
	int		columns;
	int		translation_x;
	int		translation_y;
}				t_fdf;

#endif
