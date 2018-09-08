/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 15:33:47 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/09/08 15:33:49 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    draw_line(t_fdf *fdf, t_vec p1, t_vec p2)
{
	int dx = (p2.x - p1.x >= 0 ? 1 : -1);
	int dy = (p2.y - p1.y >= 0 ? 1 : -1);

	float lengthX = fabs(p2.x - p1.x);
	float lengthY = fabs(p2.y - p1.y);

	int length = fmax(lengthX, lengthY);

	if (length == 0)
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, p1.x + WIDTH / 2, p1.y + HEIGHT / 2, p1.color);
	if (lengthY <= lengthX)
	{
		float x = p1.x;
		float y = p1.y;
		float d = -lengthX;

		length++;
		while (length--)
		{
			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x + WIDTH / 2, y + HEIGHT / 2, p1.color);
			x += dx;
			d += 2 * lengthY;
			if (d > 0)
			{
				d -= 2 * lengthX;
				y += dy;
			}
		}
	}
	else
	{
		float x = p1.x;
		float y = p1.y;
		float d = -lengthY;

		length++;
		while (length--)
		{
			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x + WIDTH / 2, y + HEIGHT / 2, p1.color);
			y += dy;
			d += 2 * lengthX;
			if (d > 0)
			{
				d -= 2 * lengthY;
				x += dx;
			}
		}
	}
}
