/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 15:33:42 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/09/10 15:33:44 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int		count_splits(char **split)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}

void			clear_split(char **split)
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

static	void	ft_error(t_fdf *fdf, char **split, char *line)
{
	if (count_splits(split) != fdf->columns)
	{
		clear_split(split);
		ft_strdel(&line);
		ft_putstr("Invalid map\n");
		system("leaks fdf");
		exit(1);
	}
}

int				parse_map(t_fdf *fdf, const char *file_name)
{
	int		fd;
	char	*line;
	char	**split;
	int		ret;

	fd = open(file_name, O_RDONLY);
	ret = get_next_line(fd, &line);
	if (ret <= 0)
		return (0);
	split = ft_strsplit(line, ' ');
	fdf->columns = count_splits(split);
	clear_split(split);
	ft_strdel(&line);
	fdf->rows++;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		split = ft_strsplit(line, ' ');
		ft_error(fdf, split, line);
		clear_split(split);
		ft_strdel(&line);
		fdf->rows++;
	}
	close(fd);
	return (1);
}
