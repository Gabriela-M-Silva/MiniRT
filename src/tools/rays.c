/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:52:31 by gde-mora          #+#    #+#             */
/*   Updated: 2023/08/13 17:46:03 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/miniRT.h"

t_ray	create_ray(t_tuple *origin, t_tuple *direction) // alterada
{
	t_ray	ray;

	pass_tuple_values(origin, &ray.origin);
	pass_tuple_values(direction, &ray.direction);
	return (ray);	
}

t_tuple	position(t_ray *ray, double time) // alterada
{
	t_tuple	temp_mult;
	t_tuple	sum;

	temp_mult = multiply_tuple(&ray->direction, time);
	sum = sum_tuples(&temp_mult, &ray->origin);
	return (sum);
}
