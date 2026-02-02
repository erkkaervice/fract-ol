/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:49:18 by eala-lah          #+#    #+#             */
/*   Updated: 2024/12/04 16:32:44 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/* Includes necessary libraries for the project.
 * - MLX42: Provides window management and graphical rendering functions.
 * - Libft: Includes common string, memory, and utility functions.
 * - Math: Offers mathematical functions used in fractal calculations.
 */
# include "../mlx42/include/MLX42/MLX42.h"
# include "../libft/inc/libft.h"
# include <math.h>

/* Constants for graphical rendering and fractal computation.
 * - WID: Window width in pixels.
 * - HEI: Window height in pixels.
 * - ZOOM_STEP: The factor by which the fractal zoom level changes.
 * - OFFSET_STEP: Step size for shifting the fractal view along the X and Y axes.
 * - MAX_ITER: The maximum number of iterations used for fractal calculations.
 */
# define WID            900
# define HEI            900
# define ZOOM_STEP      1.1
# define OFFSET_STEP    0.1
# define MAX_ITER       100

/* Key codes for user controls.
 * - ESC: Exit the program.
 * - Arrow keys: Move the fractal view in the corresponding direction.
 * - C, W, S: Interact with various controls (specific behavior may vary).
 */
# define MLX_KEY_ESCAPE 256
# define MLX_KEY_UP     265
# define MLX_KEY_DOWN   264
# define MLX_KEY_LEFT   263
# define MLX_KEY_RIGHT  262
# define MLX_KEY_C      67
# define MLX_KEY_W      87
# define MLX_KEY_S      83

/* Enum defining the supported fractal types.
 * - MANDELBROT: The Mandelbrot fractal.
 * - JULIA: The Julia fractal.
 * - PHOENIX: The Phoenix fractal.
 * - UNKNOWN_FRACTAL: Used for handling invalid or unrecognized fractal types.
 */
typedef enum e_frc_type
{
	MANDELBROT,
	JULIA,
	PHOENIX,
	UNKNOWN_FRACTAL
}	t_frc_type;

/* Structure representing the properties of a fractal.
 * - mlx: A pointer to the mlx instance used for rendering.
 * - img: A pointer to the image where the fractal is drawn.
 * - type: The current fractal type selected.
 * - zoom: The current zoom level for the fractal.
 * - offset_x, offset_y: The current position of the fractal in the window.
 * - x_scale, y_scale: Scaling factors used to adjust the fractal’s dimensions.
 * - color_mode: The current color mode for rendering the fractal.
 * - p: A parameter specific to some fractals, like the Phoenix fractal.
 */
typedef struct s_frc
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_frc_type	type;
	double		zoom;
	double		offset_x;
	double		offset_y;
	double		x_scale;
	double		y_scale;
	double		julia_re;
	double		julia_im;
	int			color_mode;
	double		p;
}	t_frc;

/* --- Fractal Rendering Functions ---
 * Functions responsible for rendering the fractals and managing image data.
 */
void	ft_render(t_frc *frc);
t_frc	*ft_launch(mlx_t *mlx, const char *frc_name, int argc, char **argv);
t_frc	*ft_freee(t_frc *frc);
void	ft_mandelbrot(int x, int y, t_frc *frc);
void	ft_julia(int x, int y, t_frc *frc);
void	ft_phoenix(int x, int y, t_frc *frc);

/* --- User Interaction Functions ---
 * Functions handling user input such as key presses and mouse scrolling.
 */
void	ft_keys(mlx_key_data_t keydata, void *param);
void	ft_zoom(t_frc *frc, int zoom_in);
void	ft_scroll(double x, double y, void *param);

/* --- Utility Functions ---
 * Functions for auxiliary tasks such as color calculation and error handling.
 */
int		ft_color(int i, int max_iter, int color_mode);
void	ft_instructions(void);
int		ft_juliarguments(char **argv, t_frc *frc);

#endif
