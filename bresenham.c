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

static	void	part_x(t_fdf *fdf, t_bresenham bresenham, t_vec p1)
{
	float	x;
	float	y;
	float	d;
	int		pixel;

	x = p1.x;
	y = p1.y;
	d = -bresenham.lengthX;
	bresenham.length++;
	while (bresenham.length--)
	{
		if ((x + WIDTH / 2) < WIDTH - 1 && (y + HEIGHT / 2) < HEIGHT - 1 &&
									(x + WIDTH / 2) > 0 && (y + HEIGHT / 2) > 0)
		{
			pixel = (int)(y + HEIGHT / 2) * WIDTH + (x + WIDTH / 2);
			fdf->image[pixel] = p1.color;
		}
		x += bresenham.dx;
		d += 2 * bresenham.lengthY;
		if (d > 0)
		{
			d -= 2 * bresenham.lengthX;
			y += bresenham.dy;
		}
	}
}

static	void	part_y(t_fdf *fdf, t_bresenham bresenham, t_vec p1)
{
	float	x;
	float	y;
	float	d;
	int		pixel;

	x = p1.x;
	y = p1.y;
	d = -bresenham.lengthY;
	bresenham.length++;
	while (bresenham.length--)
	{
		if ((x + WIDTH / 2) < WIDTH - 1 && (y + HEIGHT / 2) < HEIGHT - 1 &&
									(x + WIDTH / 2) > 0 && (y + HEIGHT / 2) > 0)
		{
			pixel = (int)(y + HEIGHT / 2) * WIDTH + (x + WIDTH / 2);
			fdf->image[pixel] = p1.color;
		}
		y += bresenham.dy;
		d += 2 * bresenham.lengthX;
		if (d > 0)
		{
			d -= 2 * bresenham.lengthY;
			x += bresenham.dx;
		}
	}
}

void			draw_line(t_fdf *fdf, t_vec p1, t_vec p2)
{
	t_bresenham bresenham;
	int			pixel;

	bresenham.dx = (p2.x - p1.x >= 0 ? 1 : -1);
	bresenham.dy = (p2.y - p1.y >= 0 ? 1 : -1);
	bresenham.lengthX = fabs(p2.x - p1.x);
	bresenham.lengthY = fabs(p2.y - p1.y);
	bresenham.length = fmax(bresenham.lengthX, bresenham.lengthY);
	if (bresenham.length == 0)
	{
		if ((p1.x + WIDTH / 2) < WIDTH - 1 && (p1.y + HEIGHT / 2) < HEIGHT - 1
		&& (p1.x + WIDTH / 2) > 0 && (p1.y + HEIGHT / 2) > 0)
		{
			pixel = fabs((int)(p1.y + HEIGHT / 2) * WIDTH + (p1.x + WIDTH / 2));
			fdf->image[pixel] = p1.color;
		}
	}
	if (bresenham.lengthY <= bresenham.lengthX)
		part_x(fdf, bresenham, p1);
	else
		part_y(fdf, bresenham, p1);
}
