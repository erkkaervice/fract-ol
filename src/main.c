/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:56:06 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/01 14:22:01 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	display_start_screen(mlx_t *mlx)
{
	int32_t x_pos;
	int32_t y_pos;

	// Get the window position
	mlx_get_window_pos(mlx, &x_pos, &y_pos);

	// Use the window position to display text
	mlx_put_string(mlx, "Select a fractal:", x_pos + 50, y_pos + 50);
	mlx_put_string(mlx, "1. Mandelbrot", x_pos + 50, y_pos + 100);
	mlx_put_string(mlx, "2. Julia", x_pos + 50, y_pos + 150);
}

void handle_start_key(mlx_key_data_t keydata, void *param)
{
	mlx_t *mlx = (mlx_t *)param;

	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == '1')
		{
			t_fractal *fractal = init_fractal(mlx);
			if (fractal)
			{
				fractal->type = MANDELBROT;
				render_fractal(fractal);
				mlx_key_hook(mlx, &handle_key, fractal);
			}
		}
		else if (keydata.key == '2')
		{
			t_fractal *fractal = init_fractal(mlx);
			if (fractal)
			{
				fractal->type = JULIA;
				render_fractal(fractal);
				mlx_key_hook(mlx, &handle_key, fractal);
			}
		}
	}
}

int	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
	if (!mlx)
	{
		ft_printf("Error: Failed to initialize MLX.\n");
		return (EXIT_FAILURE);
	}
	display_start_screen(mlx);
	mlx_key_hook(mlx, &handle_start_key, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}