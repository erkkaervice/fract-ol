/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:17:00 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/26 14:17:40 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	calculate_mandelbrot_pixel(int x, int y, t_frc *frc)
{
	double	c[2];
	double	z[2];
	int		i;
	double	tmp;
	int		color;

	c[0] = frc->x_scale * (x - WID / 2.0) / frc->zoom + frc->offset_x;
	c[1] = frc->y_scale * (y - HEI / 2.0) / frc->zoom + frc->offset_y;
	
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
	color = calculate_psychedelic_color(i, 100);
	mlx_put_pixel(frc->img, x, y, color);
}


void	render_mandelbrot(t_frc *frc)
{
	int	y;
	int	x;

	frc->x_scale = 4.0 / WID;
	frc->y_scale = 4.0 / HEI;
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
