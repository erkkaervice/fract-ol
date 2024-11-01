/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:14:30 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/01 15:13:23 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_frc	*frc;

	frc = (t_frc *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(frc->mlx);
	else if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_UP)
			frc->offset_y -= 0.1 / frc->zoom;
		else if (keydata.key == MLX_KEY_DOWN)
			frc->offset_y += 0.1 / frc->zoom;
		else if (keydata.key == MLX_KEY_LEFT)
			frc->offset_x -= 0.1 / frc->zoom;
		else if (keydata.key == MLX_KEY_RIGHT)
			frc->offset_x += 0.1 / frc->zoom;
		else if (keydata.key == MLX_KEY_Z)
			frc->zoom *= 1.1;
		else if (keydata.key == MLX_KEY_X)
			frc->zoom /= 1.1;
	}
	render_frc(frc);
}
