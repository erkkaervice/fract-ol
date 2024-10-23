/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:14:30 by eala-lah          #+#    #+#             */
/*   Updated: 2024/10/23 14:07:44 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_fractal *fractal = (t_fractal *)param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fractal->mlx);
	else if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_UP)
			fractal->offset_y -= 0.1 / fractal->zoom;
		else if (keydata.key == MLX_KEY_DOWN)
			fractal->offset_y += 0.1 / fractal->zoom;
		else if (keydata.key == MLX_KEY_LEFT)
			fractal->offset_x -= 0.1 / fractal->zoom;
		else if (keydata.key == MLX_KEY_RIGHT)
			fractal->offset_x += 0.1 / fractal->zoom;
		else if (keydata.key == MLX_KEY_Z)
			fractal->zoom *= 1.1;
		else if (keydata.key == MLX_KEY_X)
			fractal->zoom /= 1.1;
	}

	render_fractal(fractal);
}

