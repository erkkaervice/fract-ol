/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:13:07 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/01 15:28:35 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	calculate_mandelbrot_color(int i)
{
	if (i == 100)
		return (0x000000FF);
	return ((i * 255 / 100) << 16);
}

static void	calculate_mandelbrot_pixel(int x, int y, t_frc *frc)
{
	double	c[2];
	double	z[2];
	int		i;
	double	tmp;
	int		color;

	c[0] = (x - WID / 2.0) * (4.0 / WID) / frc->zoom + frc->offset_x;
	c[1] = (y - HEI / 2.0) * (4.0 / HEI) / frc->zoom + frc->offset_y;
	z[0] = 0;
	z[1] = 0;
	i = 0;
	while (z[0] * z[0] + z[1] * z[1] <= 4 && i < 100)
	{
		tmp = z[0] * z[0] - z[1] * z[1] + c[0];
		z[1] = 2 * z[0] * z[1] + c[1];
		z[0] = tmp;
		i++;
	}
	color = calculate_mandelbrot_color(i);
	mlx_put_pixel(frc->img, x, y, color);
}

void	render_mandelbrot(t_frc *frc)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEI)
	{
		x = 0;
		while (x < WID)
		{
			calculate_mandelbrot_pixel(x, y, frc);
			x++;
		}
		y++;
	}
}
