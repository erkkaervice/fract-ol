/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:16:30 by eala-lah          #+#    #+#             */
/*   Updated: 2024/12/03 17:07:29 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_coordinates(int x, int y, t_frc *frc, double *z)
{
	double	x_scale;
	double	y_scale;

	x_scale = 4.0 / WID;
	y_scale = 4.0 / HEI;
	z[0] = (x - WID / 2.0) * x_scale / frc->zoom + frc->offset_x;
	z[1] = (y - HEI / 2.0) * y_scale / frc->zoom + frc->offset_y;
}

static void	ft_iteration(double *z, int *i, double re, double im)
{
	double	tmp;

	while (z[0] * z[0] + z[1] * z[1] <= 4.0 && *i < MAX_ITER)
	{
		tmp = z[0] * z[0] - z[1] * z[1] + re;
		z[1] = 2.0 * z[0] * z[1] + im;
		z[0] = tmp;
		(*i)++;
	}
}

void	ft_mandelbrot(int x, int y, t_frc *frc)
{
	int		i;
	int		color;
	double	z[2];
	double	c[2];

	i = 0;
	ft_coordinates(x, y, frc, c);
	z[0] = 0.0;
	z[1] = 0.0;
	ft_iteration(z, &i, c[0], c[1]);
	color = ft_color(i, MAX_ITER, frc->color_mode);
	mlx_put_pixel(frc->img, x, y, color);
}

void	ft_julia(int x, int y, t_frc *frc)
{
	int		i;
	int		color;
	double	z[2];

	i = 0;
	ft_coordinates(x, y, frc, z);
	ft_iteration(z, &i, frc->julia_re, frc->julia_im);
	color = ft_color(i, MAX_ITER, frc->color_mode);
	mlx_put_pixel(frc->img, x, y, color);
}

void	ft_phoenix(int x, int y, t_frc *frc)
{
	int		i;
	int		color;
	double	z[2];

	i = 0;
	ft_coordinates(x, y, frc, z);
	ft_iteration(z, &i, frc->p, 0.0);
	color = ft_color(i, MAX_ITER, frc->color_mode);
	mlx_put_pixel(frc->img, x, y, color);
}
