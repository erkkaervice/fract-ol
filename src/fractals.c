/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:16:30 by eala-lah          #+#    #+#             */
/*   Updated: 2024/12/04 15:57:23 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * ft_coordinates - Converts pixel coordinates to complex number.
 *
 * Maps the pixel `(x, y)` to a complex number using the scaling, zoom, and 
 * offset parameters of the fractal view settings.
 *
 * Parameters:
 * - x: The x-coordinate of the pixel.
 * - y: The y-coordinate of the pixel.
 * - frc: The fractal structure containing zoom and offsets.
 * - z: A pointer to a double array where the complex number will be stored.
 */
void	ft_coordinates(int x, int y, t_frc *frc, double *z)
{
	double	x_scale;
	double	y_scale;

	x_scale = 4.0 / WID;
	y_scale = 4.0 / HEI;
	z[0] = (x - WID / 2.0) * x_scale / frc->zoom + frc->offset_x;
	z[1] = (y - HEI / 2.0) * y_scale / frc->zoom + frc->offset_y;
}

/*
 * ft_iteration - Iterates the fractal formula for a point.
 *
 * Performs iterative calculations to check if a point escapes the fractal set 
 * (i.e., its magnitude exceeds 2). Updates the complex number `z` in each 
 * iteration and tracks the number of iterations.
 *
 * Parameters:
 * - z: A pointer to the complex number array.
 * - i: A pointer to the iteration counter.
 * - re: The real part of the constant for the iteration.
 * - im: The imaginary part of the constant for the iteration.
 */
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

/*
 * ft_mandelbrot - Renders a pixel in the Mandelbrot set.
 *
 * Uses `ft_coordinates` to map the pixel to a complex number and iterates 
 * with `ft_iteration`. Sets the pixel color based on the number of iterations 
 * required to escape the set.
 *
 * Parameters:
 * - x: The x-coordinate of the pixel.
 * - y: The y-coordinate of the pixel.
 * - frc: The fractal structure containing the necessary settings.
 */
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

/*
 * ft_julia - Renders a pixel in the Julia set.
 *
 * Maps the pixel coordinates to a complex number and iterates with 
 * `ft_iteration`, using fixed Julia parameters (`julia_re`, `julia_im`) 
 * for the formula.
 *
 * Parameters:
 * - x: The x-coordinate of the pixel.
 * - y: The y-coordinate of the pixel.
 * - frc: The fractal structure containing the Julia parameters.
 */
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

/*
 * ft_phoenix - Renders a pixel in the Phoenix fractal.
 *
 * Maps the pixel coordinates to a complex number and iterates with 
 * `ft_iteration`, using a fixed parameter (`p`) for the Phoenix fractal 
 * formula.
 *
 * Parameters:
 * - x: The x-coordinate of the pixel.
 * - y: The y-coordinate of the pixel.
 * - frc: The fractal structure containing the parameter for the Phoenix fractal.
 */
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
