/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _USE_MATH_DEFINES // TODO: remove
#include <math.h>
#include "scene.h"

t_vec3f transform_translate(const t_mat4f *orien, const t_vec3f *dpos)
{
    t_vec3f translate;
    t_vec3f i;
    t_vec3f j;
    t_vec3f k;

    calculate_basis_from_orientation(orien, &i, &j, &k);
    translate.x = dpos->x * i.x + dpos->y * j.x + dpos->z * k.x;
    translate.y = dpos->x * i.y + dpos->y * j.y + dpos->z * k.y;
    translate.z = dpos->x * i.z + dpos->y * j.z + dpos->z * k.z;
    return (translate);
}

static t_vec3f	rodrigoues_rotation(const t_vec3f *v, const t_vec3f *n, const float angle)
{
    t_vec3f a;
    t_vec3f b;
    t_vec3f c;

    a = vec3f_scalar(n, vec3f_dot(v, n) * (1.0f - cos(angle)));
    b = vec3f_scalar(v, cos(angle));
    c = vec3f_cross(v, n);
    c = vec3f_scalar(&c, sin(angle));
    a = vec3f_add(&a, &b);
    return (vec3f_add(&a, &c));
}

t_mat4f transform_rotate_x(const t_mat4f *orien, const float rotx)
{
    t_vec3f i;
    t_vec3f j;
    t_vec3f k;

    calculate_basis_from_orientation(orien, &i, &j, &k);

    j = rodrigoues_rotation(&j, &i, rotx);
    k = rodrigoues_rotation(&k, &i, rotx);

    return (calculate_matrix_orientation_from_basis(&i, &j, &k));
}

t_mat4f transform_rotate_y(const t_mat4f* orien, const float roty)
{
    t_vec3f i;
    t_vec3f j;
    t_vec3f k;

    calculate_basis_from_orientation(orien, &i, &j, &k);

    i = rodrigoues_rotation(&i, &j, roty);
    k = rodrigoues_rotation(&k, &j, roty);

    return (calculate_matrix_orientation_from_basis(&i, &j, &k));
}

t_mat4f transform_rotate_z(const t_mat4f* orien, const float rotz)
{
    t_vec3f i;
    t_vec3f j;
    t_vec3f k;

    calculate_basis_from_orientation(orien, &i, &j, &k);

    i = rodrigoues_rotation(&i, &k, rotz);
    j = rodrigoues_rotation(&j, &k, rotz);

    return (calculate_matrix_orientation_from_basis(&i, &j, &k));
}
// TODO: create transform_scale
