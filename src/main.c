/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:56:06 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/01 15:14:03 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	launch_frc(mlx_t *mlx, const char *frc_name)
{
	t_frc	*frc;

	frc = init_frc(mlx);
	if (!frc)
		return ;
	if (ft_strncmp(frc_name, "mandelbrot", 11) == 0)
	{
		frc->type = MANDELBROT;
		render_frc(frc);
	}
	else if (ft_strncmp(frc_name, "julia", 6) == 0)
	{
		frc->type = JULIA;
		render_frc(frc);
	}
	else
	{
		ft_printf("Error: Unknown frc type. Use 'mandelbrot' or 'julia'.\n");
		free(frc);
		return ;
	}
	mlx_key_hook(mlx, &handle_key, frc);
}

int	main(int argc, char **argv)
{
	mlx_t	*mlx;

	if (argc != 2)
	{
		ft_printf("Usage: ./fractol [frc_type]\n");
		return (1);
	}
	mlx = mlx_init(WID, HEI, "fractol", 1);
	if (!mlx)
	{
		ft_printf("Error: Failed to initialize MLX.\n");
		return (1);
	}
	launch_frc(mlx, argv[1]);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
