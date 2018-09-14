/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:43:15 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/09/13 14:43:17 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	t_circle	init_circle(void)
{
	t_circle circle;

	circle.x0 = WIDTH / 2;
	circle.y0 = HEIGHT / 2;
	circle.radius = 150;
	circle.dx = 1;
	circle.dy = 1;
	circle.x = circle.radius - 1;
	circle.y = 0;
	circle.err = circle.dx - (circle.radius << 1);
	circle.c = 0xFF5D00;
	return (circle);
}

static	void		draw_circle(t_fdf *fdf, t_circle c)
{
	while (c.x >= c.y)
	{
		fdf->image[(c.y0 + c.y) * WIDTH + (c.x0 + c.x)] = c.c;
		fdf->image[(c.y0 + c.x) * WIDTH + (c.x0 + c.y)] = c.c;
		fdf->image[(c.y0 + c.x) * WIDTH + (c.x0 - c.y)] = c.c;
		fdf->image[(c.y0 + c.y) * WIDTH + (c.x0 - c.x)] = c.c;
		fdf->image[(c.y0 - c.y) * WIDTH + (c.x0 - c.x)] = c.c;
		fdf->image[(c.y0 - c.x) * WIDTH + (c.x0 - c.y)] = c.c;
		fdf->image[(c.y0 - c.x) * WIDTH + (c.x0 + c.y)] = c.c;
		fdf->image[(c.y0 - c.y) * WIDTH + (c.x0 + c.x)] = c.c;
		if (c.err <= 0)
		{
			c.y++;
			c.err += c.dy;
			c.dy += 2;
		}
		if (c.err > 0)
		{
			c.x--;
			c.dx += 2;
			c.err += c.dx - (c.radius << 1);
		}
	}
}

static	void		write_header(t_fdf *fdf, t_circle circle, int flag_circle)
{
	if (flag_circle == 1)
		draw_circle(fdf, circle);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	if (flag_circle == 1)
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIDTH / 2 - ALPHA_WIDTH * 6,
				(HEIGHT - ALPHA_HEIGHT) / 2, 0xFFFFFF, "PRESS ANY KEY");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIDTH / 2 - ALPHA_WIDTH - 5,
											35 - ALPHA_HEIGHT / 2, 0, "FDF");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIDTH / 2 - ALPHA_WIDTH * 4,
							HEIGHT - 35 - ALPHA_HEIGHT / 2, 0, "vbrovenk");
}

void				help(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 80, 0xFFFFFF,
													"TRANSLATION: ARROWS");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 110, 0xFFFFFF,
													"ROTATION X : W/S");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 140, 0xFFFFFF,
													"ROTATION Y : Q/E");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, 170, 0xFFFFFF,
													"ROTATION Z : A/D");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, HEIGHT - 100, 0xFFFFFF,
												"ZOOM  : Z/X");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 10, HEIGHT - 130, 0xFFFFFF,
												"DEPTH : PAGE UP/PAGE DOWN");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIDTH - 110, 80, 0xFFFFFF,
																"EXIT : ESC");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIDTH - 110, 110, 0xFFFFFF,
																"HELP : ?");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIDTH - 180, HEIGHT - 100,
											0xFFFFFF, "RESET : BACKSPACE");
}

void				draw_info(t_fdf *fdf, int flag_circle)
{
	int			x;
	int			y;
	t_circle	circle;

	circle = init_circle();
	y = -1;
	while ((x = -1) && ++y < 70)
		while (++x < WIDTH)
			fdf->image[y * WIDTH + x] = circle.c;
	while (++x < WIDTH)
		fdf->image[y * WIDTH + x] = 0xFFFFFF;
	y = HEIGHT - 71;
	x = -1;
	while (++x < WIDTH)
		fdf->image[y * WIDTH + x] = 0xFFFFFF;
	while (++y < HEIGHT && (x = -1))
		while (++x < WIDTH)
			fdf->image[y * WIDTH + x] = circle.c;
	write_header(fdf, circle, flag_circle);
}
