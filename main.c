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

int	count_splits(char **split)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	return (count);

}

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

void	print_map_vectors(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	// while (++i < fdf->rows)
	// {
	// 	j = -1;
	// 	while (++j < fdf->columns)
	// 	{
	// 		printf("fdf->map_vec[%d][%d] x = %f | y = %f | z = %f | color = %d\n",
	// 			i, j, fdf->map_vec[i][j].x, fdf->map_vec[i][j].y, fdf->map_vec[i][j].z,
	// 			fdf->map_vec[i][j].color);
	// 	}
	// 	printf("\n");
	// }
	while (++i < fdf->rows)
	{
		j = -1;
		while (++j < fdf->columns)
		{
			printf("fdf->change_map[%d][%d] x = %f | y = %f | z = %f | color = %d\n",
				i, j, fdf->change_map[i][j].x, fdf->change_map[i][j].y, fdf->change_map[i][j].z,
				fdf->change_map[i][j].color);
		}
		printf("\n");
	}
}

void	draw_vertex(t_fdf *fdf)
{
	int	i;
	int	j;

	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	i = -1;
	// while (++i < fdf->rows)
	// {
	// 	j = -1;
	// 	while (++j < fdf->columns)
	// 	{
	// 		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, fdf->map_vec[i][j].x + WIDTH / 2, 
	// 				fdf->map_vec[i][j].y + HEIGHT / 2, fdf->map_vec[i][j].color);
	// 	}
	// }
	while (++i < fdf->rows)
	{
		j = -1;
		while (++j < fdf->columns)
		{
			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, fdf->change_map[i][j].x + WIDTH / 2, 
					fdf->change_map[i][j].y + HEIGHT / 2, fdf->change_map[i][j].color);
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
		// fdf->change_map[1][1].z += fdf->translation_z;	
}

void	draw_lines(t_fdf *fdf)
{
	int	i;
	int j;

	i = 0;

	rotate(fdf);	
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	while (i < fdf->rows)
	{
		j = 0;
		while (j < fdf->columns)
		{
			if (j < fdf->columns - 1)
				draw_line(fdf, fdf->change_map[i][j], fdf->change_map[i][j + 1]);
			if (i < fdf->rows - 1)
				draw_line(fdf, fdf->change_map[i][j], fdf->change_map[i + 1][j]);
			j++;	
		}
		i++;
	}
}

void	clear_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_strdel(&split[i]);
		i++;
	}
	free(split);
}

int	parse_map(t_fdf *fdf, const char *file_name)
{
	int		fd;
	char	*line;
	char	**split;
	int		ret;

	fd = open(file_name, O_RDONLY);
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (0);
	split = ft_strsplit(line, ' ');
	fdf->columns = count_splits(split);
	clear_split(split);
	ft_strdel(&line);
	fdf->rows++;	
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		split = ft_strsplit(line, ' ');
		if (count_splits(split) != fdf->columns)
		{
			clear_split(split);
			ft_strdel(&line);
			ft_putstr("Invalid map\n");
			return (0);
		}
		clear_split(split);
		ft_strdel(&line);
		fdf->rows++;
	}
	// printf("fdf->rows = %d\n", fdf->rows);
	// printf("fdf->columns = %d\n", fdf->columns);
	close(fd);
	return (1);
}

void	create_map_vectors(t_fdf *fdf)
{
	int	i;

	fdf->map_vec = (t_vec**)malloc(sizeof(t_vec*) * fdf->rows);
	fdf->change_map = (t_vec**)malloc(sizeof(t_vec*) * fdf->rows);
	i = 0;
	while (i < fdf->rows)
	{
		fdf->map_vec[i] = (t_vec*)malloc(sizeof(t_vec) * fdf->columns);
		fdf->change_map[i] = (t_vec*)malloc(sizeof(t_vec) * fdf->columns);
		i++;
	}
}

int		set_color(char *color_str)
{
	char	**split;
	int		i;
	char	*ready_color;
	int		result;

	split = ft_strsplit(color_str, ',');
	i = 0;
	if (split[1] != NULL && split[1][0] == '0' && split[1][1] == 'x')
		result = ft_atoi_base(&split[1][2], 16);
	else if (split[1] == NULL)
		result = 0x0000FF;
	else
		result = ft_atoi_base(split[1], 16);
	clear_split(split);
	return (result);
}

void	fill_map_vectors(t_fdf *fdf, const char *file_name)
{
	char	*line;
	int		fd;
	int		i;
	int		j;
	char	**split;

	int		start_width;
	int		start_height;

	fd = open(file_name, O_RDONLY);
	i = 0;
	start_height = -fdf->height_map;
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		j = -1;
		start_width = -fdf->width_map;
		while (++j < fdf->columns)
		{
			fdf->map_vec[i][j].x = start_width;
			fdf->map_vec[i][j].y = start_height;
			fdf->map_vec[i][j].z = ft_atoi(split[j]) * BETWEEN_VERTEX;
			if (ft_strchr(split[j], ','))
				fdf->map_vec[i][j].color = set_color(split[j]);
			else if (fdf->map_vec[i][j].z > 0)
				fdf->map_vec[i][j].color = 0x0000FF;
			else
				fdf->map_vec[i][j].color = 0xFFFFFF;
			start_width += BETWEEN_VERTEX;
		}
		start_height += BETWEEN_VERTEX;
		clear_split(split);
		ft_strdel(&line);
		i++;
	}
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
	fdf->scale = 0.5;
}

int	choose_key(int key, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf*)param;
	if (key == RIGHT_ARROW)
	{
		fdf->translation_x += 10;	
	}
	else if (key == LEFT_ARROW)
	{
		fdf->translation_x -= 10;
	}
	else if (key == UP_ARROW)
	{
		fdf->translation_y -= 10;
	}
	else if (key == DOWN_ARROW)
	{
		fdf->translation_y += 10;
	}
	else if (key == UP_Z)
	{

	}
	else if (key == DOWN_Z)
	{

	}
	else if (key == A)
	{
		fdf->angle_z += 0.1;
	}
	else if (key == D)
	{
		fdf->angle_z -= 0.1;
	}
	else if (key == W)
	{
		fdf->angle_x += 0.1;
	}
	else if (key == S)
	{
		fdf->angle_x -= 0.1;
	}
	else if (key == Q)
	{
		fdf->angle_y += 0.1;
	}
	else if (key == E)
	{
		fdf->angle_y -= 0.1;
	}
	else if (key == Z)
	{
		if (fdf->scale - 0.2 > 0)
			fdf->scale -= 0.2;
	}
	else if (key == X)
	{
		fdf->scale += 0.2;
	}
	else if (key == RESET)
	{
		fdf->translation_x = 0;
		fdf->translation_y = 0;
		fdf->angle_x = 0;
		fdf->angle_y = 0;
		fdf->angle_z = 0;
		fdf->scale = 0.5;
	}
	// rotate(fdf);
	// draw_vertex(fdf);
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
			// system("leaks fdf");			
			return (0);			
		}
		create_map_vectors(fdf);
		fdf->width_map = (fdf->columns - 1) * BETWEEN_VERTEX / 2;
		fdf->height_map = (fdf->rows - 1) * BETWEEN_VERTEX / 2;
		// printf("height_map = %d\n", fdf->height_map);
		// printf("width_map = %d\n", fdf->width_map);
		
		fill_map_vectors(fdf, argv[1]);
		fill_change_vectors(fdf);

		fdf->mlx_ptr = mlx_init();
		fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "FDF");
		draw_lines(fdf);
		mlx_hook(fdf->win_ptr, 2, 5, choose_key, fdf);
		mlx_hook(fdf->win_ptr, 17, 1L << 17, x_exit, 0);
		// print_map_vectors(fdf);
		mlx_loop(fdf->mlx_ptr);
	}

	return (0);
}