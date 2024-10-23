/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:56:06 by eala-lah          #+#    #+#             */
/*   Updated: 2024/10/23 13:59:57 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(void)
{
	mlx_t		*mlx;
	t_fractal	*fractal;

	mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
	if (!mlx)
	{
		ft_printf("Error: Failed to initialize MLX.\n");
		return (EXIT_FAILURE);
	}
	fractal = init_fractal(mlx);
	if (!fractal)
		return (EXIT_FAILURE);
	render_fractal(fractal);
	mlx_key_hook(mlx, &handle_key, fractal);
	mlx_loop(mlx);
	if (fractal->img)
		mlx_delete_image(mlx, fractal->img);
	free(fractal);
	return (EXIT_SUCCESS);
}
