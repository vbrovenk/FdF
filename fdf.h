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
#include <math.h>
# include "get_next_line.h"
# include "mlx.h"

# define WIDTH 720
# define HEIGHT 480
# define UP_ARROW 126
# define DOWN_ARROW 125
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define A 0
# define D 2
# define W 13
# define S 1
# define Q 12
# define E 14
# define Z 6
# define X 7
# define UP_Z 116
# define DOWN_Z 121
# define RESET 51

# define BETWEEN_VERTEX 40

typedef	struct s_vec
{
	float	x;
	float	y;
	float	z;
	int		color;
}				t_vec;

typedef	struct	s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;

	t_vec	**map_vec;
	t_vec	**change_map;

	int		width_map;
	int		height_map;

	int		rows;
	int		columns;

	int		translation_x;
	int		translation_y;
	int		translation_z;
	float	angle_x;
	float	angle_y;
	float	angle_z;
	float	scale;
}				t_fdf;

typedef struct s_m3x3
{
	float	m[3][3];
}				t_m3x3;

t_vec	rot_x(t_fdf *fdf, t_vec point);
t_vec	rot_y(t_fdf *fdf, t_vec point);
t_vec	rot_z(t_fdf *fdf, t_vec point);
t_vec   scale(t_fdf *fdf, t_vec point);
void    draw_line(t_fdf *fdf, t_vec p1, t_vec p2);

#endif
