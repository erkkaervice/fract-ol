/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:17:34 by eala-lah          #+#    #+#             */
/*   Updated: 2024/11/22 14:51:21 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define MAX_ITER 100
# include "fractol.h"

int	calculate_color(int i, t_frc_type type);
int	calculate_psychedelic_color(int i, int max_iter);

#endif
