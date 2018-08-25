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

void	print_map_vectors(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	while (++i < fdf->rows)
	{
		j = -1;
		while (++j < fdf->columns)
		{
			printf("fdf->map_vec[%d][%d] x = %d | y = %d | z = %d | color = %d\n",
				i, j, fdf->map_vec[i][j].x, fdf->map_vec[i][j].y, fdf->map_vec[i][j].z,
				fdf->map_vec[i][j].color);
		}
		printf("\n");
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
	i = 0;
	while (i < fdf->rows)
	{
		fdf->map_vec[i] = (t_vec*)malloc(sizeof(t_vec) * fdf->columns);
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

	fd = open(file_name, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		j = -1;
		while (++j < fdf->columns)
		{
			fdf->map_vec[i][j].x = j;
			fdf->map_vec[i][j].y = i;
			fdf->map_vec[i][j].z = ft_atoi(split[j]);
			if (ft_strchr(split[j], ','))
				fdf->map_vec[i][j].color = set_color(split[j]);
			else
				fdf->map_vec[i][j].color = 0x00FF00;
		}
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
	fdf->columns = 0;
	fdf->rows = 0;
	fdf->translation_x = 0;
	fdf->translation_y = 0;
}

void	draw_lines(t_fdf *fdf)
{
	int i;
	int j;

	// fdf->mlx_ptr = mlx_init();
	// fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "FDF");
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	i = 0;
	while (i < fdf->rows)
	{
		j = 0;
		while (j < fdf->columns)
		{
			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, fdf->map_vec[i][j].x * 40 + fdf->translation_x,
						fdf->map_vec[i][j].y * 40 + fdf->translation_y,
						fdf->map_vec[i][j].color);
			j++;
		}
		i++;
	}
}

int	choose_key(int key, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf*)param;
	if (key == RIGHT_ARROW)
	{
		// mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, 200, 200, 0xFF);
		fdf->translation_x += 8;
		draw_lines(fdf);
	}
	else if (key == LEFT_ARROW)
	{
		fdf->translation_x -= 8;
		draw_lines(fdf);
	}
	else if (key == UP_ARROW)
	{
		fdf->translation_y -= 8;
		draw_lines(fdf);
	}
	else if (key == DOWN_ARROW)
	{
		fdf->translation_y += 8;
		draw_lines(fdf);
	}
	return (0);
}

int		x_exit(void *param)
{
	param = NULL;
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
			return (0);
		create_map_vectors(fdf);
		fill_map_vectors(fdf, argv[1]);

		fdf->mlx_ptr = mlx_init();
		fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "FDF");
		draw_lines(fdf);
		// mlx_key_hook(fdf->win_ptr, choose_key, fdf);
		mlx_hook(fdf->win_ptr, 2, 5, choose_key, fdf);
		mlx_hook(fdf->win_ptr, 17, 1L << 17, x_exit, 0);
		// print_map_vectors(fdf);
		mlx_loop(fdf->mlx_ptr);
	}
	// system("leaks fdf");
	return (0);
}