/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:14:30 by eala-lah          #+#    #+#             */
/*   Updated: 2024/12/03 15:14:31 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	*frc = launch_frc(*mlx, argv[1], argc, argv);
	if (!*frc)
	{
		show_usage();
		mlx_terminate(*mlx);
		return (0);
	}
	return (1);
}

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_frc	*frc;

	frc = (t_frc *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(frc->mlx);
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_UP)
			frc->offset_y -= OFFSET_STEP / frc->zoom;
		else if (keydata.key == MLX_KEY_DOWN)
			frc->offset_y += OFFSET_STEP / frc->zoom;
		else if (keydata.key == MLX_KEY_LEFT)
			frc->offset_x -= OFFSET_STEP / frc->zoom;
		else if (keydata.key == MLX_KEY_RIGHT)
			frc->offset_x += OFFSET_STEP / frc->zoom;
		else if (keydata.key == MLX_KEY_C)
			frc->color_mode = (frc->color_mode + 1) % 3;
		else if (keydata.key == MLX_KEY_W)
			frc->p += 0.01;
		else if (keydata.key == MLX_KEY_S)
			frc->p -= 0.01;
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

int	calculate_psychedelic_color(int i, int max_iter, int color_mode)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)i / (double)max_iter;
	if (color_mode == 0)
	{
		r = (int)(rand() % 256 * t);
		g = (int)(rand() % 256 * t);
		b = (int)(rand() % 256 * t);
	}
	else if (color_mode == 1)
	{
		r = (int)(9 * (1 - t) * t * t * t * 255);
		g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	else
	{
		r = (int)(255 * t);
		g = (int)(255 * t);
		b = (int)(255 * t);
	}
	return ((r << 16) | (g << 8) | b);
}
