/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:18:09 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/22 14:57:28 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	calculate_mandelbrot_color(int i)
{
	if (i == MAX_ITER)
		return (0x000000FF);
	return ((i * 255 / MAX_ITER) << 16);
}

int	calculate_julia_color(int i)
{
	if (i == MAX_ITER)
		return (0x000000FF);
	return ((i * 255 / MAX_ITER) << 8);
}

int	calculate_color(int i, t_frc_type type)
{
	if (i == MAX_ITER)
		return (0x000000FF);
	if (type == MANDELBROT)
		return ((i * 255 / MAX_ITER) << 16);
	else if (type == JULIA)
		return ((i * 255 / MAX_ITER) << 8);
	return (0x000000FF);
}

int	calculate_psychedelic_color(int i, int max_iter)
{
	int		r;
	int		g;
	int		b;
	double	t;

	r = (rand() % 255);
	g = (rand() % 255);
	b = (rand() % 255);
	t = (double)i / (double)max_iter;
	r = (int)(r * t);
	g = (int)(g * t);
	b = (int)(b * t);
	return ((r << 16) | (g << 8) | b);
}
