/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:16:30 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/27 18:36:32 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calculate_scaled_coordinates(int x, int y, t_frc *frc, double *z)
{
	z[0] = (x - WID / 2.0) * frc->x_scale / frc->zoom + frc->offset_x;
	z[1] = (y - HEI / 2.0) * frc->y_scale / frc->zoom + frc->offset_y;
}

void	pixel_julia(int x, int y, t_frc *frc)
{
	int		i;
	int		color;
	double	z[2];
	double	tmp;

	calculate_scaled_coordinates(x, y, frc, z);
	i = 0;
	while (z[0] * z[0] + z[1] * z[1] <= 4.0 && i < MAX_ITER)
	{
		tmp = z[0] * z[0] - z[1] * z[1] + frc->julia_re;
		z[1] = 2.0 * z[0] * z[1] + frc->julia_im;
		z[0] = tmp;
		i++;
	}
	color = calculate_psychedelic_color(i, MAX_ITER);
	mlx_put_pixel(frc->img, x, y, color);
}

void	pixel_mandelbrot(int x, int y, t_frc *frc)
{
	double	c[2];
	double	z[2];
	int		i;
	double	tmp;
	int		color;

	calculate_scaled_coordinates(x, y, frc, c);
	z[0] = 0;
	z[1] = 0;
	i = 0;
	while (z[0] * z[0] + z[1] * z[1] <= 4 && i < MAX_ITER)
	{
		tmp = z[0] * z[0] - z[1] * z[1] + c[0];
		z[1] = 2 * z[0] * z[1] + c[1];
		z[0] = tmp;
		i++;
	}
	color = calculate_psychedelic_color(i, MAX_ITER);
	mlx_put_pixel(frc->img, x, y, color);
}