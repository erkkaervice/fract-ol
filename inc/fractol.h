/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:49:18 by eala-lah          #+#    #+#             */
/*   Updated: 2024/12/02 16:44:45 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx42/include/MLX42/MLX42.h"
# include "../libft/inc/libft.h"
# include <math.h>

# define WID            900
# define HEI            900
# define ZOOM_STEP      1.1
# define OFFSET_STEP    0.1
# define MAX_ITER       100

# define MLX_KEY_ESCAPE 256
# define MLX_KEY_UP     265
# define MLX_KEY_DOWN   264
# define MLX_KEY_LEFT   263
# define MLX_KEY_RIGHT  262
# define MLX_KEY_C      67
# define MLX_KEY_W      87
# define MLX_KEY_S      83

typedef enum e_frc_type
{
	MANDELBROT,
	JULIA,
	PHOENIX,
	UNKNOWN_FRACTAL
}	t_frc_type;

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

void	render_frc(t_frc *frc);
t_frc	*launch_frc(mlx_t *mlx, const char *frc_name, int argc, char **argv);
void	free_frc(t_frc *frc);
void	pixel_julia(int x, int y, t_frc *frc);
void	pixel_mandelbrot(int x, int y, t_frc *frc);
void	pixel_phoenix(int x, int y, t_frc *frc);
void	handle_key(mlx_key_data_t keydata, void *param);
void	zoom_on_mouse_position(t_frc *frc, int zoom_in);
void	handle_mouse_scroll(double x, double y, void *param);
int		calculate_psychedelic_color(int i, int max_iter, int color_mode);
int		parse_julia_parameters(char **argv, t_frc *frc);

#endif
