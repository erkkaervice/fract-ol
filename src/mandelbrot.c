/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:13:07 by eala-lah          #+#    #+#             */
/*   Updated: 2024/10/23 14:15:21 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	calculate_mandelbrot_color(int i)
{
	if (i == 100)
		return (0x000000FF);
	return (i * 255 / 100) << 16;
}

static void	calculate_mandelbrot_pixel(int x, int y, t_fractal *fractal)
{
	double	c_re;
	double	c_im;
	double	z_re;
	double	z_im;
	int		i;

	c_re = (x - WIDTH / 2.0) * (4.0 / WIDTH) / fractal->zoom + fractal->offset_x;
	c_im = (y - HEIGHT / 2.0) * (4.0 / HEIGHT) / fractal->zoom + fractal->offset_y;
	z_re = 0;
	z_im = 0;
	i = 0;
	while (z_re * z_re + z_im * z_im <= 4 && i < 100)
	{
		double tmp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = tmp;
		i++;
	}
	int color = calculate_mandelbrot_color(i);
	mlx_put_pixel(fractal->img, x, y, color);
}

void	render_mandelbrot(t_fractal *fractal)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			calculate_mandelbrot_pixel(x, y, fractal);
			x++;
		}
		y++;
	}
}
