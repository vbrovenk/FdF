/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 18:05:48 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/09/11 18:05:51 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		x_exit(void *param)
{
	param = NULL;
	system("leaks fdf");
	exit(1);
	return (0);
}

static	void	reset(t_fdf *fdf)
{
	fdf->translation_x = 0;
	fdf->translation_y = 0;
	fdf->translation_z = 1;
	fdf->angle_x = 0;
	fdf->angle_y = 0;
	fdf->angle_z = 0;
	if (fdf->rows * BETWEEN_VERTEX < HEIGHT)
		fdf->scale = 1;
	else
		fdf->scale = 0.3;
	if (fdf->rows > 400)
		fdf->scale = 0.1;
}

static	void	choose_key_part2(int key, t_fdf *fdf)
{
	if (key == S)
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
		reset(fdf);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	help(fdf);
	ft_bzero(fdf->image, WIDTH * HEIGHT * sizeof(int));
	draw_lines(fdf);
	draw_info(fdf, 0);
	if (key == HELP)
		fdf->flag_help = fdf->flag_help == 0 ? 1 : 0;
	if (fdf->flag_help == 1)
			help(fdf);
}

int	choose_key(int key, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf*)param;
	if (key == 53)
		x_exit(param);
	if (key == RIGHT_ARROW)
		fdf->translation_x += 10;
	else if (key == LEFT_ARROW)
		fdf->translation_x -= 10;
	else if (key == UP_ARROW)
		fdf->translation_y -= 10;
	else if (key == DOWN_ARROW)
		fdf->translation_y += 10;
	else if (key == UP_Z)
		fdf->translation_z += 0.1;
	else if (key == DOWN_Z)
		fdf->translation_z -= 0.1;
	else if (key == A)
		fdf->angle_z += 0.1;
	else if (key == D)
		fdf->angle_z -= 0.1;
	else if (key == W)
		fdf->angle_x += 0.1;
	choose_key_part2(key, fdf);
	return (0);
}
