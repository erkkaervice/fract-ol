/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:56:06 by eala-lah          #+#    #+#             */
/*   Updated: 2024/10/18 12:59:53 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fractal	*init_fractal(mlx_t *mlx)
{
	t_fractal	*fractal;

	fractal = malloc(sizeof(t_fractal));
	if (!fractal)
		return (NULL);
	fractal->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!fractal->img)
	{
		free(fractal);
		return (NULL);
	}
	fractal->type = MANDELBROT;
	fractal->zoom = 1.0;
	fractal->offset_x = 0;
	fractal->offset_y = 0;
	fractal->color_scheme = 0;
	fractal->mlx = mlx;
	return (fractal);
}

void	render_fractal(t_fractal *fractal)
{
	int	x;
	int	y;

	// Clear the existing image
	mlx_delete_image(fractal->mlx, fractal->img);
	
	// Create a new image for rendering
	fractal->img = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (!fractal->img)
	{
		ft_printf("Failed to create new image for rendering!\n");
		return; // Handle this error appropriately
	}

	// Initialize y coordinate
	y = 0;
	while (y < HEIGHT)
	{
		// Initialize x coordinate for each row
		x = 0;
		while (x < WIDTH)
		{
			if (fractal->type == MANDELBROT)
				render_mandelbrot(fractal, x, y);
			else if (fractal->type == JULIA)
				render_julia(fractal, x, y);
			x++;
		}
		y++;
	}

	// Push the new image to the window
	mlx_image_to_window(fractal->mlx, fractal->img, 0, 0);
}

void	render_mandelbrot(t_fractal *fractal, int x, int y)
{
	int		i;
	double	c_re;
	double	c_im;
	double	z_re;
	double	z_im;
	double	z_re_sq;
	double	z_im_sq;
	int		max_iter = 100;
	int		color;

	// Map pixel (x, y) to complex plane
	c_re = (x - WIDTH / 2.0) * (4.0 / WIDTH) / fractal->zoom + fractal->offset_x;
	c_im = (y - HEIGHT / 2.0) * (4.0 / HEIGHT) / fractal->zoom + fractal->offset_y;

	// Initialize z = 0
	z_re = 0;
	z_im = 0;
	z_re_sq = 0;
	z_im_sq = 0;

	// Mandelbrot iteration
	i = 0;
	while (i < max_iter && (z_re_sq + z_im_sq) <= 4)
	{
		// z = z^2 + c
		z_im = 2 * z_re * z_im + c_im;
		z_re = z_re_sq - z_im_sq + c_re;
		z_re_sq = z_re * z_re;
		z_im_sq = z_im * z_im;
		i++;
	}

	// Choose color based on iterations
	if (i == max_iter)
		color = 0x000000FF;  // Black for points inside the Mandelbrot set
	else
		color = i * 255 / max_iter;  // Color gradient for points outside

	// Set pixel color with bounds checking
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(fractal->img, x, y, color);
}

void	render_julia(t_fractal *fractal, int x, int y)
{
	int		i;
	double	z_re;
	double	z_im;
	double	z_re_sq;
	double	z_im_sq;
	int		max_iter = 100;
	int		color;
	double	c_re = -0.7;  // Julia constant, can be user-configurable
	double	c_im = 0.27015;  // Julia constant, can be user-configurable

	// Map pixel (x, y) to complex plane
	z_re = (x - WIDTH / 2.0) * (4.0 / WIDTH) / fractal->zoom + fractal->offset_x;
	z_im = (y - HEIGHT / 2.0) * (4.0 / HEIGHT) / fractal->zoom + fractal->offset_y;
	z_re_sq = z_re * z_re;
	z_im_sq = z_im * z_im;

	// Julia iteration
	i = 0;
	while (i < max_iter && (z_re_sq + z_im_sq) <= 4)
	{
		// z = z^2 + c
		z_im = 2 * z_re * z_im + c_im;
		z_re = z_re_sq - z_im_sq + c_re;
		z_re_sq = z_re * z_re;
		z_im_sq = z_im * z_im;
		i++;
	}

	// Choose color based on iterations
	if (i == max_iter)
		color = 0x000000FF;  // Black for points inside the Julia set
	else
		color = i * 255 / max_iter;  // Color gradient for points outside

	// Set pixel color with bounds checking
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(fractal->img, x, y, color);
}

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_fractal *fractal = (t_fractal *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fractal->mlx);
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		fractal->offset_y -= 0.1 / fractal->zoom;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		fractal->offset_y += 0.1 / fractal->zoom;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		fractal->offset_x -= 0.1 / fractal->zoom;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		fractal->offset_x += 0.1 / fractal->zoom;
	else if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		fractal->zoom *= 1.2;
	else if (keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS)
		fractal->zoom /= 1.2;
	render_fractal(fractal);
}

int	main(void)
{
	mlx_t		*mlx;
	t_fractal	*fractal;

	mlx = mlx_init(WIDTH, HEIGHT, "Fractol", true);
	if (!mlx)
		return (1);
	fractal = init_fractal(mlx);
	if (!fractal)
		return (1);
	mlx_key_hook(mlx, &handle_key, fractal);
	render_fractal(fractal);  // Initial render
	mlx_loop(mlx);
	
	// Free the image before freeing the fractal
	if (fractal->img)
		free(fractal->img);  // If `img` is a pointer, use appropriate free method
	free(fractal);
	return (0);
}
