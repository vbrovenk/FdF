/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 16:57:51 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/08/21 16:57:52 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

void	fill_change_vectors(t_fdf *fdf)
{
	int i;
	int j;

	i = -1;
	while (++i < fdf->rows)
	{
		j = -1;
		while (++j < fdf->columns)
		{
			fdf->change_map[i][j].x = fdf->map_vec[i][j].x;
			fdf->change_map[i][j].y = fdf->map_vec[i][j].y;
			fdf->change_map[i][j].z = fdf->map_vec[i][j].z;
			fdf->change_map[i][j].color = fdf->map_vec[i][j].color;
		}
	}
}

void	rotate(t_fdf *fdf)
{
	int i;
	int j;

	i = -1;
	while (++i < fdf->rows)
	{
		j = -1;
		while (++j < fdf->columns)
		{
			fdf->change_map[i][j] = rot_x(fdf, fdf->map_vec[i][j]);
			fdf->change_map[i][j] = rot_y(fdf, fdf->change_map[i][j]);
			fdf->change_map[i][j] = rot_z(fdf, fdf->change_map[i][j]);
			fdf->change_map[i][j] = scale(fdf, fdf->change_map[i][j]);
			fdf->change_map[i][j].x += fdf->translation_x;
			fdf->change_map[i][j].y += fdf->translation_y;
		}
	}
}

void	draw_lines(t_fdf *fdf)
{
	int i;
	int j;

	rotate(fdf);
	i = -1;
	while (++i < fdf->rows)
	{
		j = -1;
		while (++j < fdf->columns)
		{
			if (j < fdf->columns - 1)
				draw_line(fdf, fdf->change_map[i][j], fdf->change_map[i][j + 1]);
			if (i < fdf->rows - 1)
				draw_line(fdf, fdf->change_map[i][j], fdf->change_map[i + 1][j]);
		}
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}

void	init_struct(t_fdf *fdf)
{
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
	fdf->map_vec = NULL;
	fdf->change_map = NULL;
	fdf->columns = 0;
	fdf->rows = 0;
	fdf->translation_x = 0;
	fdf->translation_y = 0;
	fdf->translation_z = 0;
	fdf->angle_x = 0;
	fdf->angle_y = 0;
	fdf->angle_z = 0;
}

int	choose_key(int key, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf*)param;
	if (key == RIGHT_ARROW)
		fdf->translation_x += 10;	
	else if (key == LEFT_ARROW)
		fdf->translation_x -= 10;
	else if (key == UP_ARROW)
		fdf->translation_y -= 10;
	else if (key == DOWN_ARROW)
		fdf->translation_y += 10;
	else if (key == UP_Z)
	{

	}
	else if (key == DOWN_Z)
	{

	}
	else if (key == A)
		fdf->angle_z += 0.1;
	else if (key == D)
		fdf->angle_z -= 0.1;
	else if (key == W)
		fdf->angle_x += 0.1;
	else if (key == S)
		fdf->angle_x -= 0.1;
	else if (key == Q)
		fdf->angle_y += 0.1;
	else if (key == E)
		fdf->angle_y -= 0.1;
	else if (key == Z)
	{
		if (fdf->scale > 0.01)
			fdf->scale -= 0.01;
	}
	else if (key == X)
		fdf->scale += 0.01;
	else if (key == RESET)
	{
		fdf->translation_x = 0;
		fdf->translation_y = 0;
		fdf->angle_x = 0;
		fdf->angle_y = 0;
		fdf->angle_z = 0;
	}
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	ft_bzero(fdf->image, WIDTH * HEIGHT * sizeof(int));
	draw_lines(fdf);

	return (0);
}

int		x_exit(void *param)
{
	param = NULL;
	// system("leaks fdf");
	exit(1);
	return (0);
}

// compilation without FLAGS
// доделать парсинг карты, если левые символы
int main(int argc, char const **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
		ft_putstr("Usage : ./fdf <filename>\n");
	else
	{
		fdf = (t_fdf*)malloc(sizeof(t_fdf));
		init_struct(fdf);
		if (parse_map(fdf, argv[1]) == 0)
		{
			system("leaks fdf");
			return (0);
		}
		create_map_vectors(fdf);
		fdf->width_map = (fdf->columns - 1) * BETWEEN_VERTEX / 2;
		fdf->height_map = (fdf->rows - 1) * BETWEEN_VERTEX / 2;
		
		fill_map_vectors(fdf, argv[1]);
		fill_change_vectors(fdf);

		fdf->mlx_ptr = mlx_init();
		fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "FDF");

		fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
		fdf->image = (int *)mlx_get_data_addr(fdf->img_ptr, &fdf->bits_per_pixel, &fdf->size_line, &fdf->endian);
		draw_lines(fdf);
		mlx_hook(fdf->win_ptr, 2, 5, choose_key, fdf);
		mlx_hook(fdf->win_ptr, 17, 1L << 17, x_exit, 0);
		mlx_loop(fdf->mlx_ptr);
	}
	return (0);
}
