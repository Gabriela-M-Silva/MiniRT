/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_scene.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:42:37 by gsmereka          #+#    #+#             */
/*   Updated: 2023/11/03 18:57:31 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_SCENE_H
# define DEFINE_SCENE_H
# include "../../headers/miniRT.h"

t_HIT	*closest_hit(t_SCENE *scene, t_ray *ray);
void	render_scene(t_SCENE *scene, t_CAMERA *camera, t_data *data);
void	prepare_ray(t_ray *ray, t_CAMERA *camera, double j, double i);
t_tuple	trace_color(t_SCENE *scene, t_ray *object_ray, t_ray *light_ray);
t_HIT	*intersect_sphere(t_token *sphere, t_ray *ray);
double	LIGHT_at(t_POINTLIGHT *light, t_HIT *hit);
void	init_ray(t_ray *ray, t_tuple *origin, t_tuple *direction);

#endif
