/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:49:18 by eala-lah          #+#    #+#             */
/*   Updated: 2024/10/23 14:03:24 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx42/include/MLX42/MLX42.h"
# include "../libft/inc/libft.h"
# include "keys.h"
# include <math.h>

# define WIDTH 900
# define HEIGHT 900

typedef enum e_fractal_type
{
	MANDELBROT,
	JULIA
}	t_fractal_type;

typedef struct s_fractal
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_fractal_type	type;
	double			zoom;
	double			offset_x;
	double			offset_y;
}	t_fractal;

t_fractal	*init_fractal(mlx_t *mlx);
void		render_fractal(t_fractal *fractal);
void		render_mandelbrot(t_fractal *fractal);
void		render_julia(t_fractal *fractal);
void		handle_key(mlx_key_data_t keydata, void *param);

#endif
