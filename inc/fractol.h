/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:49:18 by eala-lah          #+#    #+#             */
/*   Updated: 2024/10/18 12:53:41 by eala-lah         ###   ########.fr       */
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

# define MANDELBROT 1
# define JULIA 2

typedef struct s_fractal
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	int				type;
	double			zoom;
	double			offset_x;
	double			offset_y;
	int				color_scheme;
}	t_fractal;

// Function declarations
void	render_mandelbrot(t_fractal *fractal, int x, int y);
void	render_julia(t_fractal *fractal, int x, int y);
void	render_fractal(t_fractal *fractal);

#endif
