/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:56:06 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/27 14:04:54 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdbool.h>
#include <ctype.h>

bool	is_valid_float(const char *str)
{
	int		i;
	bool	dot_seen;

	i = 0;
	dot_seen = false;
	while (str[i] && isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (dot_seen)
				return (false);
			dot_seen = true;
		}
		else if (!isdigit(str[i]))
		{
			return (false);
		}
		i++;
	}
	return (i > 0 && (dot_seen || isdigit(str[i - 1])));
}

double	ft_atof(const char *str)
{
	double	result;
	double	decimal_factor;
	bool	is_negative;

	result = 0.0;
	decimal_factor = 0.1;
	is_negative = false;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		is_negative = (*str == '-');
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			result += (*str - '0') * decimal_factor;
			decimal_factor *= 0.1;
			str++;
		}
	}
	return (is_negative ? -result : result);
}

void	show_usage(void)
{
	ft_printf("Usage: ./fractol [fractal_type] [options]\n");
	ft_printf("Available fractals:\n");
	ft_printf(" - mandelbrot\n");
	ft_printf(" - julia <real_part> <imaginary_part>\n");
	ft_printf("    Example: ./fractol julia -0.8 0.156\n");
}

int	main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_frc	*frc;

	if (argc < 2 || (ft_strncmp(argv[1], "julia", 5) == 0 && argc != 4))
	{
		ft_putendl_fd("Error: Julia parameters must be valid floating-point numbers.", 2);
		show_usage();
		return (1);
	}
	mlx = mlx_init(WID, HEI, "fractol", 1);
	if (!mlx)
		ft_error("Error: Failed to initialize MLX.\n");
	frc = launch_frc(mlx, argv[1]);
	if (!frc)
	{
		show_usage();
		mlx_terminate(mlx);
		return (1);
	}
	if (frc->type == JULIA)
	{
		if (!is_valid_float(argv[2]) || !is_valid_float(argv[3]))
		{
			ft_putendl_fd("Error: Julia parameters must be valid floating-point numbers.", 2);
			free_frc(frc);
			mlx_terminate(mlx);
			return (1);
		}
		frc->julia_re = ft_atof(argv[2]);
		frc->julia_im = ft_atof(argv[3]);
	}
	mlx_scroll_hook(frc->mlx, &handle_mouse_scroll, frc);
	mlx_loop(mlx);
	free_frc(frc);
	mlx_terminate(mlx);
	return (0);
}
