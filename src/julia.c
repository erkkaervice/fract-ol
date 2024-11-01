/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:14:22 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/01 15:25:02 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	calculate_julia_color(int i)
{
	if (i == 100)
		return (0x000000FF);
	return ((i * 255 / 100) << 8);
}

static void	calculate_julia_pixel(int x, int y, t_frc *frc, double c_re)
{
	double	z[2];
	int		i;
	double	tmp;
	int		color;

	z[0] = (x - WID / 2.0) * (4.0 / WID) / frc->zoom + frc->offset_x;
	z[1] = (y - HEI / 2.0) * (4.0 / HEI) / frc->zoom + frc->offset_y;
	i = 0;
	while (z[0] * z[0] + z[1] * z[1] <= 4 && i < 100)
	{
		tmp = z[0] * z[0] - z[1] * z[1] + c_re;
		z[1] = 2 * z[0] * z[1] + 0.27015;
		z[0] = tmp;
		i++;
	}
	color = calculate_julia_color(i);
	mlx_put_pixel(frc->img, x, y, color);
}

void	render_julia(t_frc *frc)
{
	int		y;
	int		x;
	double	c_re;

	c_re = -0.7;
	y = 0;
	while (y < HEI)
	{
		x = 0;
		while (x < WID)
		{
			calculate_julia_pixel(x, y, frc, c_re);
			x++;
		}
		y++;
	}
}
