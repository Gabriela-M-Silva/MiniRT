/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:53:06 by gsmereka          #+#    #+#             */
/*   Updated: 2024/03/26 18:44:57 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/miniRT.h"

static double	calculate_distance(t_token *cylinder, t_ray *ray);
static double	calculate_discriminant(t_intersect *intersect,
					t_token *cylinder, t_ray *ray);
static	t_tuple	normalize_cylinder(t_token *cylinder, t_ray *ray, 
					t_tuple *hit_point);
static double	distance_two_points(t_tuple *hit_point, t_tuple *ray_origin); //passar esse pra tuple tools
static t_tuple	get_init_cap(t_token *cylinder);

t_hit	*intersect_cylinder(t_token *cylinder, t_ray *ray)
{
	double		distance;
	t_tuple		hit_point;
	t_tuple		normal;
	t_hit		*hit;

	// intersect_caps();
	distance = calculate_distance(cylinder, ray);
	if (!distance)
		return (NULL);
	hit_point = ray_position(ray, distance);

	if (distance_two_points(&hit_point, &cylinder->coordinate) > cylinder->height/2)
		return (NULL);
	
	normal = normalize_cylinder(cylinder, ray, &hit_point);
	hit = init_hit(cylinder, &normal, distance, &hit_point);

	
	
	return (hit);
}

static double	calculate_distance(t_token *cylinder, t_ray *ray)
{
	t_intersect	intersect;
	double		discriminant;
	double		distance;

	intersect = (t_intersect){0};
	discriminant = calculate_discriminant(&intersect, cylinder, ray);
	if (discriminant <= EPSILON || intersect.a < EPSILON) //verifica divisão por 0 // < ou <= ?
		return (0);
	intersect.solutions[0] = (-intersect.b - sqrt(discriminant)) / (2 * intersect.a);
	intersect.solutions[1] = (-intersect.b + sqrt(discriminant)) / (2 * intersect.a);
	
	
	
	
	
	if (intersect.solutions[0] <= EPSILON && intersect.solutions[1] <= EPSILON) //ou só < ?
		return (0);
	// onde eu adiciono verificação com lista de caps iniciais e finais? não pode estar além do cap 
	if (intersect.solutions[0] < intersect.solutions[1] && intersect.solutions[0] < INFINITY && intersect.solutions[0] > -INFINITY) //colocar teste de infinity //assim n mudou nd
		distance = intersect.solutions[0];
	else if (intersect.solutions[1] < INFINITY && intersect.solutions[1] > -INFINITY) //assim n muda nd
		distance = intersect.solutions[1];
	else
		distance = 0.0;
	return (distance);
}

static double	calculate_discriminant(t_intersect *intersect,
	t_token *cylinder, t_ray *ray)
{
	double	d;
	t_tuple	distance_to_center;

	//a   = D|D - (D|V)^2
	intersect->a = dot_product(&ray->direction, &ray->direction) - \
		pow(dot_product(&ray->direction, &cylinder->normalized_3d_direction), 2);
	
	//b = = 2 * (D|X - (D|V)*(X|V))
	distance_to_center = subtract_tuples(&ray->origin, &cylinder->coordinate);
    intersect->b = 2 * (dot_product(&ray->direction, &distance_to_center) - \
		dot_product(&ray->direction, &cylinder->normalized_3d_direction) * \
		dot_product(&distance_to_center, &cylinder->normalized_3d_direction));
    
	//c   = X|X - (X|V)^2 - r*r
	intersect->c = dot_product(&distance_to_center, &distance_to_center) - \
		pow(dot_product(&distance_to_center, &cylinder->normalized_3d_direction), 2) - \
		cylinder->radius * cylinder->radius;
	
	d = (intersect->b * intersect->b) - (4 * intersect->a * intersect->c);
	return (d);
}

static	t_tuple	normalize_cylinder(t_token *cylinder, t_ray *ray, t_tuple *hit_point)
{
	t_tuple	normal;
	t_tuple	distance_to_center;
	double	t;
	double	m;
	

	/* Obtained t is actually the distance of the hit point from the ray origin. 
	If t is negative, the hit point lies behind the origin, and is beyond our interest 
	(except the CSG case, in which the point may interest us unless all hit points of the 
	shape are behind the origin).*/
	
	//m = D|V*t + X|V
	t = distance_two_points(hit_point, &ray->origin);
	distance_to_center = subtract_tuples(&ray->origin, &cylinder->coordinate);
    m = dot_product(&ray->direction, &cylinder->normalized_3d_direction) * t + \
		dot_product(&distance_to_center, &cylinder->normalized_3d_direction);
	
	// problema de norma abaixo nas criações de variavel
	
	//N = nrm( P-C-V*m )
	t_tuple	cylinder_cap = get_init_cap(cylinder);
	t_tuple	p_diff_c = subtract_tuples(hit_point, &cylinder_cap); //P é ray->origin msm? --n, é o centro + raio?? --hit point?
	t_tuple v_multiply_by_m = multiply_tuple(&cylinder->normalized_3d_direction, m);
	normal = subtract_tuples(&p_diff_c, &v_multiply_by_m);
	normalize_tuple(&normal);
	return (normal);

	/*There are two points on the cylinder that we hit (it can be the same point twice). 
	We have to calculate two m values and test whether they fall in the range of [0,maxm]. 
	If any falls out, we can either throw the point that corresponds to it away (the cylinder
	will have a hole) or we can cap the cylinder with planes. 
	One of the planes is defined by a pair (C,-V) and the other by (C+V*maxm,V). 
	We hit the planes like a typical plane; the dot products we have already calculated, we 
	only need to do the division(s).*/
	// eu n fiz os testes de min e max, adc isso?  --- la na parte de escolher qual hit usar
}

static double	distance_two_points(t_tuple *hit_point, t_tuple *ray_origin)
{
	double	distance;
	double	x_diff;
	double	y_diff;
	double	z_diff;

	// ray_origin - hit_point ou hit_point - ray_origin?  ----faz diferença? --acho q n
	x_diff = ray_origin->x - hit_point->x;
	y_diff = ray_origin->y - hit_point->y;
	z_diff = ray_origin->z - hit_point->z;
	distance = sqrt(pow(x_diff, 2) + pow(y_diff, 2) + pow(z_diff, 2));
	return (distance);
}

static t_tuple	get_init_cap(t_token *cylinder)
{
	t_tuple	cap;
	double	x;
	double	y;
	double	z;

	x = cylinder->normalized_3d_direction.x + cylinder->height/2 + cylinder->coordinate.x;
	y = cylinder->normalized_3d_direction.y + cylinder->height/2 + cylinder->coordinate.y;
	z = cylinder->normalized_3d_direction.z + cylinder->height/2 + cylinder->coordinate.z;
	cap = create_point(x, y, z);
	return (cap);
}
