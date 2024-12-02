/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:16:30 by eala-lah          #+#    #+#             */
/*   Updated: 2024/12/02 12:44:13 by eala-lah         ###   ########.fr       */
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
	color = calculate_psychedelic_color(i, MAX_ITER, frc->color_mode);
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
	color = calculate_psychedelic_color(i, MAX_ITER, frc->color_mode);
	mlx_put_pixel(frc->img, x, y, color);
}

void	calculate_phoenix_z(double *z, double *c, double p)
{
	double	tmp_real;
	double	tmp_prev_re;
	double	tmp_prev_im;

	tmp_real = z[0] * z[0] - z[1] * z[1] + c[0] + p * z[2];
	tmp_prev_re = z[0];
	tmp_prev_im = z[1];
	z[1] = 2.0 * z[0] * z[1] + c[1] + p * z[3];
	z[0] = tmp_real;
	z[2] = tmp_prev_re;
	z[3] = tmp_prev_im;
}

void	calculate_phoenix(int x, int y, t_frc *frc, double *c)
{
	c[0] = (x - WID / 2.0) * 4.0 / (WID * frc->zoom) + frc->offset_x;
	c[1] = (y - HEI / 2.0) * 4.0 / (HEI * frc->zoom) + frc->offset_y;
}

void	pixel_phoenix(int x, int y, t_frc *frc)
{
	double	z[4];
	double	c[2];
	int		i;
	int		color;

	z[0] = 0.0;
	z[1] = 0.0;
	z[2] = 0.0;
	z[3] = 0.0;
	calculate_phoenix(x, y, frc, c);
	i = 0;
	while (z[0] * z[0] + z[1] * z[1] <= 4.0 && i < MAX_ITER)
	{
		calculate_phoenix_z(z, c, frc->p);
		i++;
	}
	if (i < MAX_ITER)
		color = calculate_psychedelic_color(i - log2(log2(z[0] \
			* z[0] + z[1] * z[1])) + 4, MAX_ITER, frc->color_mode);
	else
		color = 0x000000;
	mlx_put_pixel(frc->img, x, y, color);
}
