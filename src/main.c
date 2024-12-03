/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:56:06 by eala-lah          #+#    #+#             */
/*   Updated: 2024/12/03 15:33:28 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	show_usage(void)
{
	ft_printf("Usage: ./fractol [fractal_type] [parameters]\n");
	ft_printf("Available fractals:\n");
	ft_printf(" - mandelbrot\n");
	ft_printf(" - julia <real_part> <imaginary_part>\n");
	ft_printf("    Example: ./fractol julia -0.8 0.156\n");
	ft_printf(" - phoenix\n");
}

int	main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_frc	*frc;

	if (!validate_and_initialize(argc, argv, &mlx, &frc))
		return (1);
	if (frc->type == JULIA && !parse_julia_parameters(argv, frc))
	{
		free_frc(frc);
		mlx_terminate(mlx);
		return (1);
	}
	mlx_key_hook(frc->mlx, &handle_key, frc);
	mlx_scroll_hook(frc->mlx, &handle_mouse_scroll, frc);
	mlx_loop(mlx);
	free_frc(frc);
	mlx_terminate(mlx);
	return (0);
}
