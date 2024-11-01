/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:13:11 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/01 15:09:58 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_frc	*init_frc(mlx_t *mlx)
{
	t_frc	*frc;

	frc = malloc(sizeof(t_frc));
	if (!frc)
	{
		ft_printf("Error: Failed to allocate frc structure.\n");
		return (NULL);
	}
	frc->img = mlx_new_image(mlx, WID, HEI);
	if (!frc->img)
	{
		ft_printf("Error: Failed to create image.\n");
		free(frc);
		return (NULL);
	}
	frc->type = MANDELBROT;
	frc->zoom = 1.0;
	frc->offset_x = 0;
	frc->offset_y = 0;
	frc->mlx = mlx;
	return (frc);
}

void	render_frc(t_frc *frc)
{
	if (!frc->img)
	{
		ft_printf("Error: No image to render.\n");
		return ;
	}
	if (frc->type == MANDELBROT)
		render_mandelbrot(frc);
	else if (frc->type == JULIA)
		render_julia(frc);
	mlx_image_to_window(frc->mlx, frc->img, 0, 0);
}
