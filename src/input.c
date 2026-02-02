/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:14:30 by eala-lah          #+#    #+#             */
/*   Updated: 2024/12/04 15:53:31 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * ft_keys - Handles keypress events to control the fractal rendering.
 *
 * This function listens for key events such as panning, zooming, changing 
 * color modes, and adjusting parameters (e.g., `p`). The function handles both 
 * key presses and releases, responding to keys like ESC (exit), arrow keys 
 * (pan), C (cycle colors), and W/S (adjust `p`).
 *
 * Parameters:
 * - keydata: The keypress data containing information about the key event.
 * - param: A pointer to the fractal structure to modify its state.
 */
void	ft_keys(mlx_key_data_t keydata, void *param)
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
	ft_render(frc);
}

/*
 * ft_zoom - Adjusts the zoom level of the fractal based on the mouse cursor's 
 * position.
 *
 * The zoom level is adjusted relative to the position of the mouse cursor. 
 * The zoom operation is controlled by a factor defined by `ZOOM_STEP` and 
 * modifies both the fractal's scale and position. The zoom is always centered 
 * around the mouse position to ensure intuitive zooming.
 *
 * Parameters:
 * - frc: The fractal structure containing zoom, offset, and scale data.
 * - zoom_in: A flag (1 for zooming in, 0 for zooming out) to control the 
 * zoom direction.
 */
void	ft_zoom(t_frc *frc, int zoom_in)
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

/*
 * ft_scroll - Adjusts the zoom level based on mouse scroll direction.
 *
 * This function listens for mouse wheel scroll events and adjusts the fractal 
 * zoom level based on the direction of the scroll. It calls `ft_zoom()` to 
 * modify the zoom level relative to the cursor position, providing a 
 * user-friendly zooming experience.
 *
 * Parameters:
 * - x: The x-coordinate of the mouse (not used in this function).
 * - y: The y-coordinate of the mouse, indicating the scroll direction 
 * (positive for zoom-in, negative for zoom-out).
 * - param: A pointer to the fractal structure, passed as a void pointer.
 */
void	ft_scroll(double x, double y, void *param)
{
	t_frc	*frc;

	(void)x;
	frc = (t_frc *)param;
	if (y > 0)
		ft_zoom(frc, 1);
	else
		ft_zoom(frc, 0);
	ft_render(frc);
}

/*
 * ft_color - Calculates the color of a fractal pixel based on iteration count
 * and selected color mode.
 *
 * This function produces only green and blue colors because the red channel 
 * is effectively inactive in the formula used to calculate the color. In each 
 * mode, the formula generates values for the red, green, and blue channels, 
 * but only the green and blue components contribute to the final color output. 
 * The final color is created by bit-shifting the values of the red, green, and 
 * blue channels into a 24-bit integer, where the red component is either 
 * minimized or not used at all.
 *
 * - Mode 0: Generates a color based on the iteration count, with green and blue 
 *   components creating shades of cyan and teal.
 * - Mode 1: Inverts the color scheme, with the center remaining darker 
 *   (transparent) and the edges displaying layers of blue and green shades.
 * - Mode 2: A simpler gradient where the color intensity increases from dark 
 *   to lighter blue/green as the iteration count grows.
 *
 * The function returns a 24-bit integer representing the color in RGB format, 
 * where the red, green, and blue components are packed into the integer.
 *
 * Parameters:
 * - i: The current iteration number.
 * - max_iter: The maximum number of iterations before the fractal escapes.
 * - color_mode: The selected color mode (0, 1, or 2).
 *
 * Returns:
 * - A 24-bit integer representing the color in RGB format.
 */
int	ft_color(int i, int max_iter, int color_mode)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)i / (double)max_iter;
	if (color_mode == 0)
	{
		r = (int)((i * 97 + 23) % 256 * t);
		g = (int)((i * 97 + 24) % 256 * t);
		b = (int)((i * 97 + 25) % 256 * t);
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
