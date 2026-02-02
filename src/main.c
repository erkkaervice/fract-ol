/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:56:06 by eala-lah          #+#    #+#             */
/*   Updated: 2024/12/04 16:27:02 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * ft_instructions - Displays a help message with usage instructions for the
 * program.
 *
 * This function is called when the user provides invalid input, such as
 * incorrect parameters or missing arguments. It explains the expected
 * command-line arguments and gives examples for each supported fractal type.
 */
void	ft_instructions(void)
{
	ft_printf("Usage: ./fractol [fractal_type] [parameters]\n");
	ft_printf("Available fractals:\n");
	ft_printf(" - mandelbrot\n");
	ft_printf(" - julia <real_part> <imaginary_part>\n");
	ft_printf("    Example: ./fractol julia -0.8 0.156\n");
	ft_printf("    Example: ./fractol julia -0.75 0.170\n");
	ft_printf(" - phoenix\n");
}

/*
 * ft_validate - Validates the program arguments and initializes the MLX and
 * fractal structures.
 *
 * This function checks the validity of the command-line arguments. If the
 * arguments are invalid (e.g., missing or incorrect fractal types), it calls
 * `ft_instructions()` to show the correct usage. It also initializes the MLX
 * window and creates the fractal structure using the provided fractal type and
 * parameters.
 *
 * If initialization fails at any point, it returns 0, indicating that the
 * program cannot proceed. Otherwise, it returns 1 to indicate that everything
 * is set up correctly.
 *
 * Parameters:
 * - argc: The number of command-line arguments.
 * - argv: The array of command-line argument values.
 * - mlx: The pointer to the MLX instance.
 * - frc: The pointer to the fractal structure.
 *
 * Returns:
 * - 1 if everything is initialized successfully, 0 otherwise.
 */
int	ft_validate(int argc, char **argv, mlx_t **mlx, t_frc **frc)
{
	if (argc < 2 || (ft_strncmp(argv[1], "julia", 5) == 0 && argc != 4))
	{
		ft_instructions();
		return (0);
	}
	*mlx = mlx_init(WID, HEI, "fractol", 1);
	if (!*mlx)
		ft_error("Error: Failed to initialize MLX.\n");
	*frc = ft_launch(*mlx, argv[1], argc, argv);
	if (!*frc)
	{
		ft_instructions();
		mlx_terminate(*mlx);
		return (0);
	}
	return (1);
}

/*
 * ft_juliarguments - Parses and validates the parameters for the Julia set.
 *
 * This function checks if the parameters provided for the Julia fractal (real
 * and imaginary parts) are valid floating-point numbers. It uses the
 * `ft_isfloat()` function to verify the validity of the input and then converts
 * the strings to floating-point numbers using `ft_atof()`. The converted values
 * are stored in the `frc` structure (which represents the fractal).
 *
 * If the parameters are invalid, an error message is printed and the function
 * returns 0. If the parameters are valid, the function returns 1 to indicate
 * success.
 *
 * Parameters:
 * - argv: The array of command-line argument values.
 * - frc: The fractal structure where the Julia parameters will be stored.
 *
 * Returns:
 * - 1 if the parameters are valid, 0 otherwise.
 */
int	ft_juliarguments(char **argv, t_frc *frc)
{
	if (!ft_isfloat(argv[2]) || !ft_isfloat(argv[3]))
	{
		ft_error("Error: Parameters must be valid floating-point numbers.\n");
		return (0);
	}
	frc->julia_re = ft_atof(argv[2]);
	frc->julia_im = ft_atof(argv[3]);
	return (1);
}

/*
 * main - Entry point of the program that runs the fractal rendering.
 *
 * This is the main function that drives the program. It first calls
 * `ft_validate()` to check if the input arguments are valid and initializes
 * the MLX and fractal structures. If the fractal type is "julia", it calls
 * `ft_juliarguments()` to parse and validate the Julia parameters. If anything
 * fails, the program exits with an error message.
 *
 * Once everything is validated, it enters the MLX event loop by calling
 * `mlx_loop()` which keeps the window open for the user to interact with.
 * Finally, it cleans up the allocated memory and terminates the MLX window when
 * the program exits.
 *
 * Parameters:
 * - argc: The number of command-line arguments.
 * - argv: The array of command-line argument values.
 *
 * Returns:
 * - 0 if the program runs successfully, 1 if there is an error.
 */
int	main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_frc	*frc;

	if (!ft_validate(argc, argv, &mlx, &frc))
		return (1);
	if (frc->type == JULIA && !ft_juliarguments(argv, frc))
	{
		ft_freee(frc);
		mlx_terminate(mlx);
		return (1);
	}
	mlx_loop(mlx);
	ft_freee(frc);
	mlx_terminate(mlx);
	return (0);
}
