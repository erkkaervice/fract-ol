/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:56:06 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/01 15:55:22 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_frc	*launch_frc(mlx_t *mlx, const char *frc_name)
{
	t_frc	*frc;

	frc = init_frc(mlx);
	if (!frc)
		return (NULL);
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
		return (NULL);
	}
	mlx_key_hook(mlx, &handle_key, frc);
	return (frc);
}

void	free_frc(t_frc *frc)
{
	if (frc)
	{
		if (frc->img)
			mlx_delete_image(frc->mlx, frc->img);
		free(frc);
	}
}

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
