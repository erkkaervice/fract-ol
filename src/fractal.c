/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:13:11 by eala-lah          #+#    #+#             */
/*   Updated: 2024/12/03 15:36:17 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_frc_type	get_frc_type(const char *name)
{
	if (ft_strncmp(name, "mandelbrot", 11) == 0)
		return (MANDELBROT);
	else if (ft_strncmp(name, "julia", 6) == 0)
		return (JULIA);
	else if (ft_strncmp(name, "phoenix", 8) == 0)
		return (PHOENIX);
	else
		return (UNKNOWN_FRACTAL);
}

t_frc	*init_frc(mlx_t *mlx)
{
	t_frc	*frc;

	frc = malloc(sizeof(t_frc));
	if (!frc)
	{
		ft_error("Error: Failed to allocate fractal structure.");
		return (NULL);
	}
	frc->img = mlx_new_image(mlx, WID, HEI);
	if (!frc->img)
	{
		ft_error("Error: Failed to create image.");
		free(frc);
		return (NULL);
	}
	frc->type = MANDELBROT;
	frc->zoom = 1.0;
	frc->offset_x = 0.0;
	frc->offset_y = 0.0;
	frc->julia_re = -0.8;
	frc->julia_im = 0.156;
	frc->mlx = mlx;
	frc->color_mode = 0;
	frc->p = 0.27;
	return (frc);
}

void	render_frc(t_frc *frc)
{
	int	x;
	int	y;

	frc->x_scale = 4.0 / WID;
	frc->y_scale = 4.0 / HEI;
	y = 0;
	while (y < HEI)
	{
		x = 0;
		while (x < WID)
		{
			if (frc->type == MANDELBROT)
				pixel_mandelbrot(x, y, frc);
			else if (frc->type == JULIA)
				pixel_julia(x, y, frc);
			else if (frc->type == PHOENIX)
				pixel_phoenix(x, y, frc);
			x++;
		}
		y++;
	}
	mlx_image_to_window(frc->mlx, frc->img, 0, 0);
}

t_frc	*launch_frc(mlx_t *mlx, const char *frc_name, int argc, char **argv)
{
	t_frc		*frc;
	t_frc_type	type;

	type = get_frc_type(frc_name);
	if (type == UNKNOWN_FRACTAL)
	{
		ft_printf("Error: Unknown fractal type.\n");
		return (NULL);
	}
	frc = init_frc(mlx);
	if (!frc)
		return (NULL);
	frc->type = type;
	if (type == JULIA && argc == 4)
	{
		if (!parse_julia_parameters(argv, frc))
		{
			free_frc(frc);
			return (NULL);
		}
	}
	render_frc(frc);
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
