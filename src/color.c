/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:18:09 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/27 14:22:10 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	calculate_psychedelic_color(int i, int max_iter)
{
	int		r;
	int		g;
	int		b;
	double	t;

	r = (rand() % 256);
	g = (rand() % 256);
	b = (rand() % 256);
	t = (double)i / (double)max_iter;
	r = (int)(r * t);
	g = (int)(g * t);
	b = (int)(b * t);
	return ((r << 16) | (g << 8) | b);
}

