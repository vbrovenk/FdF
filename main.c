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

#include "fdf.h"

int	count_splits(char **split)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	return (count);

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
	printf("fdf->rows = %d\n", fdf->rows);
	printf("fdf->columns = %d\n", fdf->columns);
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

void	fill_map_vectors(t_fdf *fdf, char *file_name)
{
	char	*line;
	int		fd;
	int		x;
	int		y;

	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		
	}
}

void	init_struct(t_fdf *fdf)
{
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
	fdf->map_vec = NULL;
	fdf->columns = 0;
	fdf->rows = 0;
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
	}
	// system("leaks fdf");
	return (0);
}