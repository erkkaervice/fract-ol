/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:49:18 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/01 15:26:18 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx42/include/MLX42/MLX42.h"
# include "../libft/inc/libft.h"
# include "keys.h"
# include <math.h>

# define WID 900
# define HEI 900

typedef enum e_frc_type
{
	MANDELBROT,
	JULIA
}	t_frc_type;

typedef struct s_frc
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_frc_type		type;
	double			zoom;
	double			offset_x;
	double			offset_y;
}	t_frc;

t_frc	*init_frc(mlx_t *mlx);
void	render_frc(t_frc *frc);
void	render_mandelbrot(t_frc *frc);
void	render_julia(t_frc *frc);
void	handle_key(mlx_key_data_t keydata, void *param);

#endif
