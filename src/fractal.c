/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:13:11 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/01 14:22:02 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fractal	*init_fractal(mlx_t *mlx)
{
	t_fractal	*fractal;

	fractal = malloc(sizeof(t_fractal));
	if (!fractal)
	{
		ft_printf("Error: Failed to allocate fractal structure.\n");
		return (NULL);
	}
	fractal->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!fractal->img)
	{
		ft_printf("Error: Failed to create image.\n");
		free(fractal);
		return (NULL);
	}
	fractal->type = MANDELBROT;
	fractal->zoom = 1.0;
	fractal->offset_x = 0;
	fractal->offset_y = 0;
	fractal->mlx = mlx;
	return (fractal);
}

void	render_fractal(t_fractal *fractal)
{
	if (!fractal->img)
	{
		ft_printf("Error: No image to render.\n");
		return;
	}

	if (fractal->type == MANDELBROT)
		render_mandelbrot(fractal);
	else if (fractal->type == JULIA)
		render_julia(fractal);

	mlx_image_to_window(fractal->mlx, fractal->img, 0, 0);
}
