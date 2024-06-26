/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:04:48 by gsmereka          #+#    #+#             */
/*   Updated: 2024/03/30 01:29:46 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/miniRT.h"

static t_hit	*intersect_object(t_scene *scene, t_ray *ray, int i);

t_hit	*closest_hit(t_scene *scene, t_ray *ray)
{
	t_hit	*hit;
	t_hit	*closest_hit;
	int		i;

	i = 0;
	hit = NULL;
	closest_hit = NULL;
	while (scene->objects[i])
	{
		hit = intersect_object(scene, ray, i);
		if (hit && (!closest_hit
				|| (closest_hit->distance - hit->distance >= EPSILON \
				&& hit->distance < closest_hit->distance)))
		{
			free(closest_hit);
			closest_hit = hit;
		}
		else if (hit)
			free(hit);
		i++;
	}
	return (closest_hit);
}

static t_hit	*intersect_object(t_scene *scene, t_ray *ray, int i)
{
	t_hit	*hit;

	hit = NULL;
	if (scene->objects[i]->type == SPHERE)
		hit = intersect_sphere(scene->objects[i], ray);
	else if (scene->objects[i]->type == PLANE)
		hit = intersect_plane(scene->objects[i], ray);
	else if (scene->objects[i]->type == CYLINDER)
		hit = intersect_cylinder(scene->objects[i], ray);
	return (hit);
}
