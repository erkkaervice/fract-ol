/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:14:22 by eala-lah          #+#    #+#             */
/*   Updated: 2024/10/30 15:07:19 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	calculate_julia_color(int i)
{
	if (i == 100)
		return (0x000000FF);
	return (i * 255 / 100) << 8;
}

static void	calculate_julia_pixel(int x, int y, t_fractal *fractal, double c_re, double c_im)
{
	double	z_re;
	double	z_im;
	int		i;

	z_re = (x - WIDTH / 2.0) * (4.0 / WIDTH) / fractal->zoom + fractal->offset_x;
	z_im = (y - HEIGHT / 2.0) * (4.0 / HEIGHT) / fractal->zoom + fractal->offset_y;
	i = 0;
	while (z_re * z_re + z_im * z_im <= 4 && i < 100)
	{
		double tmp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = tmp;
		i++;
	}
	int color = calculate_julia_color(i);
	mlx_put_pixel(fractal->img, x, y, color);
}

void	render_julia(t_fractal *fractal)
{
	int	y;
	int	x;
	double	c_re = -0.7;
	double	c_im = 0.27015;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			calculate_julia_pixel(x, y, fractal, c_re, c_im);
			x++;
		}
		y++;
	}
}