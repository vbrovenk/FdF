/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 15:58:49 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/09/10 15:58:51 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	fill_change_vectors(t_fdf *fdf)
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

void			create_map_vectors(t_fdf *fdf)
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
	fdf->width_map = (fdf->columns - 1) * BETWEEN_VERTEX / 2;
	fdf->height_map = (fdf->rows - 1) * BETWEEN_VERTEX / 2;
	if (fdf->rows < fdf->columns)
		fdf->scale = (float)(WIDTH / (float)(80 * fdf->columns));
	else
		fdf->scale = (float)(HEIGHT / (float)(80 * fdf->rows));
}

static	int		set_color(char *color_str)
{
	char	**split;
	int		i;
	int		result;

	split = ft_strsplit(color_str, ',');
	i = 0;
	if (split[1] != NULL && split[1][0] == '0' && split[1][1] == 'x')
		result = ft_atoi_base(&split[1][2], 16);
	else if (split[1] == NULL)
		result = 0xFF5D00;
	else
		result = ft_atoi_base(split[1], 16);
	clear_split(split);
	return (result);
}

static	void	set_coordinates(t_fdf *fdf, char **split, int i, int j)
{
	fdf->map_vec[i][j].x = fdf->start_width;
	fdf->map_vec[i][j].y = fdf->start_height;
	fdf->map_vec[i][j].z = ft_atoi(split[j]) * BETWEEN_VERTEX / 2;
	if (fdf->map_vec[i][j].z > 0)
		fdf->map_vec[i][j].depth = 1;
	else
		fdf->map_vec[i][j].depth = 0;
	if (ft_strchr(split[j], ','))
		fdf->map_vec[i][j].color = set_color(split[j]);
	else if (fdf->map_vec[i][j].z > 0)
		fdf->map_vec[i][j].color = 0xFF5D00;
	else
		fdf->map_vec[i][j].color = 0xFFFFFF;
}

void			fill_map_vectors(t_fdf *fdf, const char *file_name)
{
	char	*line;
	int		fd;
	int		i;
	int		j;
	char	**split;

	fd = open(file_name, O_RDONLY);
	i = 0;
	fdf->start_height = -fdf->height_map;
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		j = -1;
		fdf->start_width = -fdf->width_map;
		while (++j < fdf->columns)
		{
			set_coordinates(fdf, split, i, j);
			fdf->start_width += BETWEEN_VERTEX;
		}
		fdf->start_height += BETWEEN_VERTEX;
		clear_split(split);
		ft_strdel(&line);
		i++;
	}
	fill_change_vectors(fdf);
}
