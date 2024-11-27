/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:14:30 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/27 18:43:52 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_frc	*frc;

	frc = (t_frc *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			free_frc(frc);
			mlx_close_window(frc->mlx);
		}
		else if (keydata.key == MLX_KEY_UP)
			frc->offset_y -= OFFSET_STEP / frc->zoom;
		else if (keydata.key == MLX_KEY_DOWN)
			frc->offset_y += OFFSET_STEP / frc->zoom;
		else if (keydata.key == MLX_KEY_LEFT)
			frc->offset_x -= OFFSET_STEP / frc->zoom;
		else if (keydata.key == MLX_KEY_RIGHT)
			frc->offset_x += OFFSET_STEP / frc->zoom;
	}
	render_frc(frc);
}

void	zoom_on_mouse_position(t_frc *frc, int zoom_in)
{
	int		mouse_x;
	int		mouse_y;
	double	mouse_re;
	double	mouse_im;
	double	zoom_factor;

	mlx_get_mouse_pos(frc->mlx, &mouse_x, &mouse_y);
	mouse_re = (mouse_x - WID / 2.0) * (4.0 / WID) / frc->zoom + frc->offset_x;
	mouse_im = (mouse_y - HEI / 2.0) * (4.0 / HEI) / frc->zoom + frc->offset_y;
	if (zoom_in)
		zoom_factor = ZOOM_STEP;
	else
		zoom_factor = 1.0 / ZOOM_STEP;
	frc->zoom *= zoom_factor;
	frc->offset_x = mouse_re - (mouse_x - WID / 2.0) * (4.0 / WID) / frc->zoom;
	frc->offset_y = mouse_im - (mouse_y - HEI / 2.0) * (4.0 / HEI) / frc->zoom;
	frc->x_scale = 4.0 / WID / frc->zoom;
	frc->y_scale = 4.0 / HEI / frc->zoom;
}

void	handle_mouse_scroll(double x, double y, void *param)
{
	t_frc	*frc;

	(void)x;
	frc = (t_frc *)param;
	if (y > 0)
		zoom_on_mouse_position(frc, 1);
	else
		zoom_on_mouse_position(frc, 0);
	render_frc(frc);
}

int	calculate_psychedelic_color(int i, int max_iter)
{
	int		r;
	int		g;
	int		b;
	double	t;

	r = (rand() % 256);
	g = (rand() % 256);
	b = (rand() % 256);
	t = (double)i / (double)max_iter;
	r = (int)(r * t);
	g = (int)(g * t);
	b = (int)(b * t);
	return ((r << 16) | (g << 8) | b);
}
