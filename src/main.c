/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:56:06 by eala-lah          #+#    #+#             */
/*   Updated: 2024/12/03 17:24:15 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_instructions(void)
{
	ft_printf("Usage: ./fractol [fractal_type] [parameters]\n");
	ft_printf("Available fractals:\n");
	ft_printf(" - mandelbrot\n");
	ft_printf(" - julia <real_part> <imaginary_part>\n");
	ft_printf("    Example: ./fractol julia -0.8 0.156\n");
	ft_printf("    Example: ./fractol julia -0.75 0.170\n");
	ft_printf(" - phoenix\n");
}

int	ft_validate(int argc, char **argv, mlx_t **mlx, t_frc **frc)
{
	if (argc < 2 || (ft_strncmp(argv[1], "julia", 5) == 0 && argc != 4))
	{
		ft_instructions();
		return (0);
	}
	*mlx = mlx_init(WID, HEI, "fractol", 1);
	if (!*mlx)
		ft_error("Error: Failed to initialize MLX.\n");
	*frc = ft_launch(*mlx, argv[1], argc, argv);
	if (!*frc)
	{
		ft_instructions();
		mlx_terminate(*mlx);
		return (0);
	}
	return (1);
}

int	ft_juliarguments(char **argv, t_frc *frc)
{
	if (!ft_isfloat(argv[2]) || !ft_isfloat(argv[3]))
	{
		ft_error("Error: Parameters must be valid floating-point numbers.\n");
		return (0);
	}
	frc->julia_re = ft_atof(argv[2]);
	frc->julia_im = ft_atof(argv[3]);
	return (1);
}

int	main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_frc	*frc;

	if (!ft_validate(argc, argv, &mlx, &frc))
		return (1);
	if (frc->type == JULIA && !ft_juliarguments(argv, frc))
	{
		ft_freee(frc);
		mlx_terminate(mlx);
		return (1);
	}
	mlx_loop(mlx);
	ft_freee(frc);
	mlx_terminate(mlx);
	return (0);
}
