/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:49:18 by eala-lah          #+#    #+#             */
/*   Updated: 2024/12/03 17:28:22 by eala-lah         ###   ########.fr       */
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

void	ft_render(t_frc *frc);
t_frc	*ft_launch(mlx_t *mlx, const char *frc_name, int argc, char **argv);
t_frc	*ft_freee(t_frc *frc);
void	ft_mandelbrot(int x, int y, t_frc *frc);
void	ft_julia(int x, int y, t_frc *frc);
void	ft_phoenix(int x, int y, t_frc *frc);
void	ft_keys(mlx_key_data_t keydata, void *param);
void	ft_zoom(t_frc *frc, int zoom_in);
void	ft_scroll(double x, double y, void *param);
int		ft_color(int i, int max_iter, int color_mode);
void	ft_instructions(void);
int		ft_juliarguments(char **argv, t_frc *frc);

#endif