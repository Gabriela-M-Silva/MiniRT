/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:09:10 by gsmereka          #+#    #+#             */
/*   Updated: 2023/10/31 23:10:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/miniRT.h"

t_HIT	intersect_sphere(t_token *sphere, t_ray *ray)
{
	t_HIT	hit;
	double	a;
	double	b;
	double	c;
	double	delta;
	t_tuple	s0_p0;
	double	sqrt_delta;
	double	bhaskara_1;
	double	bhaskara_2;
	double	bhaskara_result;
	double	distance;
	t_tuple	hit_point;
	t_tuple	normal;

	hit = (t_HIT){0};
	a = dot_product(&ray->direction, &ray->direction);
	s0_p0 = subtract_tuples(&ray->origin, &sphere->coordinate);
	b = 2.0 * dot_product(&ray->direction, &s0_p0);
	c = dot_product(&s0_p0, &s0_p0) - (sphere->ratio * sphere->ratio);
	// printf("%f\n", a); de vez em quando da um erro de nao inicialização
	// printf("%f\n", c);
	// printf("%f\n", b);
	delta = (b * b) - (4.0 * a * c);
	// if (delta > 0)
	// // {
	// 	sqrt_delta = sqrt(delta);
		// bhaskara_1 = (-b + sqrt_delta)/(2.0 * a);
	// 	bhaskara_2 = (-b - sqrt_delta)/(2.0 * a);
	// 	if (bhaskara_1 < bhaskara_2)
	// 		bhaskara_result = bhaskara_1;
	// 	else
	// 		bhaskara_result = bhaskara_2;
	// 	if(bhaskara_result > 0)
	// 	{
	// 		distance = bhaskara_result;
	// 		hit_point = ray_position(ray, distance);
	// 		normal = subtract_tuples(&hit_point, &sphere->coordinate);
	// 		normalize_tuple(&normal);
	// 		hit = init_HIT(sphere, &normal, distance, &hit_point);
	// 		hit.valid = 1;
	// 		return (hit);
	// 	}
	// }
	return (hit);
}
