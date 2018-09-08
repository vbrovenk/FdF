/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotatin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 14:58:17 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/09/08 14:58:19 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static  t_vec	mult_vec_matrix(t_vec point, t_m3x3 matrix)
{
	t_vec	result;

	result.x = point.x * matrix.m[0][0] + point.y * matrix.m[1][0] + point.z * matrix.m[2][0];
	result.y = point.x * matrix.m[0][1] + point.y * matrix.m[1][1] + point.z * matrix.m[2][1];
	result.z = point.x * matrix.m[0][2] + point.y * matrix.m[1][2] + point.z * matrix.m[2][2];
	result.color = point.color;

	return (result);
}

t_vec	rot_x(t_fdf *fdf, t_vec point)
{
	t_vec	new_point;
	t_m3x3 	rotation;

	rotation.m[0][0] = 1;
	rotation.m[0][1] = 0;
	rotation.m[0][2] = 0;

	rotation.m[1][0] = 0;
	rotation.m[1][1] = cos(fdf->angle_x);
	rotation.m[1][2] = -sin(fdf->angle_x);

	rotation.m[2][0] = 0;
	rotation.m[2][1] = sin(fdf->angle_x);
	rotation.m[2][2] = cos(fdf->angle_x);

	new_point = mult_vec_matrix(point, rotation);
	return (new_point);
}

t_vec	rot_y(t_fdf *fdf, t_vec point)
{
	t_vec	new_point;
	t_m3x3 	rotation;

	rotation.m[0][0] = cos(fdf->angle_y);
	rotation.m[0][1] = 0;
	rotation.m[0][2] = sin(fdf->angle_y);;

	rotation.m[1][0] = 0;
	rotation.m[1][1] = 1;
	rotation.m[1][2] = 0;

	rotation.m[2][0] = -sin(fdf->angle_y);
	rotation.m[2][1] = 0;
	rotation.m[2][2] = cos(fdf->angle_y);

	new_point = mult_vec_matrix(point, rotation);
	return (new_point);
}

t_vec	rot_z(t_fdf *fdf, t_vec point)
{
	t_vec	new_point;
	t_m3x3 	rotation;

	rotation.m[0][0] = cos(fdf->angle_z);
	rotation.m[0][1] = -sin(fdf->angle_z);
	rotation.m[0][2] = 0;

	rotation.m[1][0] = sin(fdf->angle_z);
	rotation.m[1][1] = cos(fdf->angle_z);
	rotation.m[1][2] = 0;

	rotation.m[2][0] = 0;
	rotation.m[2][1] = 0;
	rotation.m[2][2] = 1;

	new_point = mult_vec_matrix(point, rotation);
	return (new_point);
}

t_vec   scale(t_fdf *fdf, t_vec point)
{
    t_vec new_point;
    t_m3x3  scale_matrix;

    scale_matrix.m[0][0] = fdf->scale;
    scale_matrix.m[0][1] = 0;
    scale_matrix.m[0][2] = 0;
    
    scale_matrix.m[1][0] = 0;
    scale_matrix.m[1][1] = fdf->scale;
    scale_matrix.m[1][2] = 0;

    scale_matrix.m[2][0] = 0;
    scale_matrix.m[2][1] = 0;
    scale_matrix.m[2][2] = fdf->scale;

    new_point = mult_vec_matrix(point, scale_matrix);
    return (new_point);
}
