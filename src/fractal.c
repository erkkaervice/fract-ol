/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:13:11 by eala-lah          #+#    #+#             */
/*   Updated: 2024/12/04 16:13:56 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * ft_selection - Selects a fractal type based on the input string.
 *
 * Maps the input string to the corresponding fractal type (`MANDELBROT`, 
 * `JULIA`, `PHOENIX`). If no match is found, returns `UNKNOWN_FRACTAL`.
 *
 * Parameters:
 * - name: The name of the fractal type as a string.
 *
 * Returns:
 * - The corresponding fractal type (`MANDELBROT`, `JULIA`, `PHOENIX`, or 
 *   `UNKNOWN_FRACTAL`).
 */
t_frc_type	ft_selection(const char *name)
{
	if (ft_strncmp(name, "mandelbrot", 11) == 0)
		return (MANDELBROT);
	if (ft_strncmp(name, "julia", 6) == 0)
		return (JULIA);
	if (ft_strncmp(name, "phoenix", 8) == 0)
		return (PHOENIX);
	return (UNKNOWN_FRACTAL);
}

/*
 * ft_initialize - Initializes the fractal structure and creates an image.
 *
 * Allocates memory for the fractal structure, creates an image, and sets 
 * initial values for the fractal properties such as zoom, offsets, and color 
 * mode. If initialization fails, returns `NULL`.
 *
 * Parameters:
 * - mlx: The mlx instance used for creating images.
 *
 * Returns:
 * - A pointer to the initialized fractal structure, or `NULL` if 
 *   initialization fails.
 */
t_frc	*ft_initialize(mlx_t *mlx)
{
	t_frc	*frc;

	frc = malloc(sizeof(t_frc));
	if (!frc)
	{
		ft_error("Error: Failed to allocate fractal structure.");
		return (NULL);
	}
	frc->img = mlx_new_image(mlx, WID, HEI);
	if (!frc->img)
	{
		ft_error("Error: Failed to create image.");
		free(frc);
		return (NULL);
	}
	frc->mlx = mlx;
	frc->zoom = 1.0;
	frc->offset_x = 0.0;
	frc->offset_y = 0.0;
	frc->color_mode = 0;
	frc->p = 0.27;
	return (frc);
}

/*
 * ft_render - Renders the fractal to the screen based on the selected type.
 *
 * Iterates through all the pixels, computing the color for each pixel based 
 * on the selected fractal type (`MANDELBROT`, `JULIA`, or `PHOENIX`). 
 * Finally, the image is displayed on the window using `mlx_image_to_window`.
 *
 * Parameters:
 * - frc: The fractal structure containing the fractal's properties, such as 
 *   zoom, offsets, and type.
 */
void	ft_render(t_frc *frc)
{
	int	x;
	int	y;

	frc->x_scale = 4.0 / WID;
	frc->y_scale = 4.0 / HEI;
	y = 0;
	while (y < HEI)
	{
		x = 0;
		while (x < WID)
		{
			if (frc->type == MANDELBROT)
				ft_mandelbrot(x, y, frc);
			else if (frc->type == JULIA)
				ft_julia(x, y, frc);
			else if (frc->type == PHOENIX)
				ft_phoenix(x, y, frc);
			x++;
		}
		y++;
	}
	mlx_image_to_window(frc->mlx, frc->img, 0, 0);
}

/*
 * ft_launch - Initializes fractal rendering and sets up event hooks.
 *
 * Selects the fractal type based on the name, initializes the fractal 
 * structure, and sets specific parameters for the Julia fractal (if 
 * applicable). Renders the fractal and sets up event hooks for user 
 * interaction, such as keypress and scroll events.
 *
 * Parameters:
 * - mlx: The mlx instance used for rendering.
 * - frc_name: The name of the fractal type as a string.
 * - argc: The number of arguments passed to the program.
 * - argv: The argument values passed to the program.
 *
 * Returns:
 * - A pointer to the initialized fractal structure, or `NULL` if there 
 *   was an error (e.g., unknown fractal type).
 */
t_frc	*ft_launch(mlx_t *mlx, const char *frc_name, int argc, char **argv)
{
	t_frc		*frc;
	t_frc_type	type;

	type = ft_selection(frc_name);
	if (type == UNKNOWN_FRACTAL)
	{
		ft_printf("Error: Unknown fractal type.\n");
		return (NULL);
	}
	frc = ft_initialize(mlx);
	if (!frc)
		return (NULL);
	frc->type = type;
	if (type == JULIA && argc == 4)
	{
		if (!ft_juliarguments(argv, frc))
			ft_freee(frc);
	}
	ft_render(frc);
	mlx_key_hook(mlx, &ft_keys, frc);
	mlx_scroll_hook(frc->mlx, &ft_scroll, frc);
	return (frc);
}

/*
 * ft_freee - Frees the memory allocated for the fractal structure and image.
 *
 * Frees the memory associated with the fractal structure and its image to 
 * prevent memory leaks.
 *
 * Parameters:
 * - frc: The fractal structure to be freed.
 *
 * Returns:
 * - `NULL` to indicate the structure has been freed.
 */
t_frc	*ft_freee(t_frc *frc)
{
	if (frc)
	{
		if (frc->img)
			mlx_delete_image(frc->mlx, frc->img);
		free(frc);
	}
	return (NULL);
}
