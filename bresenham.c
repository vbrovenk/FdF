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

float			get_coeff(int middle, int left, int right)
{
	if (right == left)
		return (0);
	return ((float)(middle - left) / (right - left));
}

int				get_gradient(int color1, int color2, float coeff)
{
	t_gradient	grad1;
	t_gradient	grad2;
	t_gradient	result;

	grad1.alpha = (color1 & 0xFF000000) >> 24;
	grad1.red = (color1 & 0x00FF0000) >> 16;
	grad1.green = (color1 & 0x0000FF00) >> 8;
	grad1.blue = color1 & 0x000000FF;
	grad2.alpha = (color2 & 0xFF000000) >> 24;
	grad2.red = (color2 & 0x00FF0000) >> 16;
	grad2.green = (color2 & 0x0000FF00) >> 8;
	grad2.blue = color2 & 0x000000FF;
	result.alpha = grad1.alpha + coeff * (grad2.alpha - grad1.alpha);
	result.red = grad1.red + coeff * (grad2.red - grad1.red);
	result.green = grad1.green + coeff * (grad2.green - grad1.green);
	result.blue = grad1.blue + coeff * (grad2.blue - grad1.blue);
	return ((result.alpha << 24) | (result.red << 16) | (result.green << 8)
																| result.blue);
}

static	void	part_x(t_fdf *fdf, t_bresenham bresenham, t_vec p1, t_vec p2)
{
	float	x;
	float	y;
	float	d;
	int		pixel;

	x = p1.x;
	y = p1.y;
	d = -bresenham.lengthX;
	while (bresenham.length--)
	{
		if ((x + WIDTH / 2) < WIDTH - 1 && (y + HEIGHT / 2) < HEIGHT - 1 &&
									(x + WIDTH / 2) > 0 && (y + HEIGHT / 2) > 0)
		{
			pixel = (int)(y + HEIGHT / 2) * WIDTH + (x + WIDTH / 2);
			fdf->image[pixel] = get_gradient(p1.color, p2.color,
											get_coeff(x, p1.x, p2.x));
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

static	void	part_y(t_fdf *fdf, t_bresenham bresenham, t_vec p1, t_vec p2)
{
	float	x;
	float	y;
	float	d;
	int		pixel;

	x = p1.x;
	y = p1.y;
	d = -bresenham.lengthY;
	while (bresenham.length--)
	{
		if ((x + WIDTH / 2) < WIDTH - 1 && (y + HEIGHT / 2) < HEIGHT - 1 &&
									(x + WIDTH / 2) > 0 && (y + HEIGHT / 2) > 0)
		{
			pixel = (int)(y + HEIGHT / 2) * WIDTH + (x + WIDTH / 2);
			fdf->image[pixel] = get_gradient(p1.color, p2.color,
												get_coeff(y, p1.y, p2.y));
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
	bresenham.length++;
	if (bresenham.lengthY <= bresenham.lengthX)
		part_x(fdf, bresenham, p1, p2);
	else
		part_y(fdf, bresenham, p1, p2);
}
