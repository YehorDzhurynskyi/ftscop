/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor.c                                            :+:      :+:    :+:   */
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

void    calculate_basis_from_rotation(const t_vec3f *rot,
                                      t_vec3f *i,
                                      t_vec3f *j,
                                      t_vec3f *k)
{
    t_mat4f orien;

    orien = calculate_matrix_rotation(rot);
    calculate_basis_from_orientation(&orien, i, j, k);
}

void    calculate_basis_from_orientation(const t_mat4f *orien,
                                         t_vec3f *i,
                                         t_vec3f *j,
                                         t_vec3f *k)
{
    *i = (t_vec3f) { orien->s0, orien->s4, orien->s8 };
    *j = (t_vec3f) { orien->s1, orien->s5, orien->s9 };
    *k = (t_vec3f) { -orien->s2, -orien->s6, -orien->sa };
}

t_mat4f calculate_matrix_scale(const t_vec3f *scl)
{
    t_mat4f scale;

    scale = mat4f_identity();
    scale.data[0][0] = scl->x;
    scale.data[1][1] = scl->y;
    scale.data[2][2] = scl->z;
    scale.data[3][3] = 1.0f;
    return (scale);
}

t_mat4f calculate_matrix_rotation(const t_vec3f *rot)
{
    t_mat4f rotation;
    t_vec3f s;
    t_vec3f c;

    c.x = cosf(rot->x * (M_PI / 180.0f));
    c.y = cosf(rot->y * (M_PI / 180.0f));
    c.z = cosf(rot->z * (M_PI / 180.0f));
    s.x = sinf(rot->x * (M_PI / 180.0f));
    s.y = sinf(rot->y * (M_PI / 180.0f));
    s.z = sinf(rot->z * (M_PI / 180.0f));
    rotation = mat4f_identity();
    rotation.data[0][0] = c.y * c.z;
    rotation.data[0][1] = -c.y * s.z;
    rotation.data[0][2] = s.y;
    rotation.data[1][0] = s.x * s.y * c.z + c.x * s.z;
    rotation.data[1][1] = -s.x * s.y * s.z + c.x * c.z;
    rotation.data[1][2] = -s.x * c.y;
    rotation.data[2][0] = -c.x * s.y * c.z + s.x * s.z;
    rotation.data[2][1] = c.x * s.y * s.z + s.x * c.z;
    rotation.data[2][2] = c.x * c.y;
    return (rotation);
}

t_mat4f calculate_matrix_translation(const t_vec3f *pos)
{
    t_mat4f translation;

    translation = mat4f_identity();
    translation.data[3][0] = pos->x;
    translation.data[3][1] = pos->y;
    translation.data[3][2] = pos->z;
    return (translation);
}

t_mat4f actor_calculate_matrix_model(const t_actor *actor)
{
    t_mat4f scale;
    t_mat4f rotation;
    t_mat4f translation;
    t_mat4f sr;

    scale = calculate_matrix_scale(&actor->scale);
    rotation = calculate_matrix_rotation(&actor->rotation);
    translation = calculate_matrix_translation(&actor->position);
    sr = mat4f_mat4f_mult(&scale, &rotation);
    return (mat4f_mat4f_mult(&sr, &translation));
}