/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:18:50 by gsmereka          #+#    #+#             */
/*   Updated: 2023/11/04 14:47:13 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/miniRT.h"

double	LIGHT_at(t_POINTLIGHT *light, t_HIT *hit)
{
	t_tuple	direction;
	double	distance;
	double	cos_theta;
	double	result;

	direction = subtract_tuples(&light->position, &hit->position);
	distance = tuple_magnitude(&direction);
	normalize_tuple(&direction);
	cos_theta = dot_product(&direction, &hit->normal);
	result = light->intensity * (cos_theta / (distance * distance));
	return (result);
}