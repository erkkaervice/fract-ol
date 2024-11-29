/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:56:06 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/29 14:51:11 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	show_usage(void)
{
	ft_printf("Usage: ./fractol [fractal_type] [options]\n");
	ft_printf("Available fractals:\n");
	ft_printf(" - mandelbrot\n");
	ft_printf(" - julia <real_part> <imaginary_part>\n");
	ft_printf("    Example: ./fractol julia -0.8 0.156\n");
	ft_printf(" - phoenix\n");
}

int	validate_and_initialize(int argc, char **argv, mlx_t **mlx, t_frc **frc)
{
	if (argc < 2 || (ft_strncmp(argv[1], "julia", 5) == 0 && argc != 4))
	{
		show_usage();
		return (0);
	}
	*mlx = mlx_init(WID, HEI, "fractol", 1);
	if (!*mlx)
		ft_error("Error: Failed to initialize MLX.\n");
	*frc = launch_frc(*mlx, argv[1]);
	if (!*frc)
	{
		show_usage();
		mlx_terminate(*mlx);
		return (0);
	}
	return (1);
}

int	parse_julia_parameters(char **argv, t_frc *frc)
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

	if (!validate_and_initialize(argc, argv, &mlx, &frc))
		return (1);
	if (frc->type == JULIA && !parse_julia_parameters(argv, frc))
	{
		free_frc(frc);
		mlx_terminate(mlx);
		return (1);
	}
	frc->zoom = 1.0;
	frc->offset_x = 0.0;
	frc->offset_y = 0.0;
	mlx_scroll_hook(frc->mlx, &handle_mouse_scroll, frc);
	mlx_loop(mlx);
	free_frc(frc);
	mlx_terminate(mlx);
	return (0);
}
