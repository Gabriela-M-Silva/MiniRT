/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_scene.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:42:37 by gsmereka          #+#    #+#             */
/*   Updated: 2023/11/04 15:11:22 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_SCENE_H
# define DEFINE_SCENE_H
# include "../../headers/miniRT.h"

t_hit	*closest_hit(t_SCENE *scene, t_ray *ray);
void	render_scene(t_SCENE *scene, t_CAMERA *camera, t_data *data);
void	calculate_ray_direction(t_ray *ray, t_CAMERA *camera, double j, double i);
t_tuple	trace_ray(t_SCENE *scene, t_ray *object_ray, t_ray *light_ray);
t_hit	*intersect_sphere(t_token *sphere, t_ray *ray);
void	normalize_ray(t_ray *ray, t_tuple *origin, t_tuple *direction);

#endif
