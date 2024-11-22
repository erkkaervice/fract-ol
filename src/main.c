/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:56:06 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/22 14:07:43 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_frc	*frc;

	if (argc != 2)
		ft_error("Usage: ./fractol [fractal_type]\n");
	mlx = mlx_init(WID, HEI, "fractol", 1);
	if (!mlx)
		ft_error("Error: Failed to initialize MLX.\n");
	frc = launch_frc(mlx, argv[1]);
	if (!frc)
	{
		mlx_terminate(mlx);
		return (1);
	}
	mlx_loop(mlx);
	free_frc(frc);
	mlx_terminate(mlx);
	return (0);
}
