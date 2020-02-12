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

static t_mat4f  calculate_matrix_scale(const t_actor *actor)
{
    t_mat4f scale;

    scale = mat4f_identity();
    scale.data[0][0] = actor->scale.x;
    scale.data[1][1] = actor->scale.y;
    scale.data[2][2] = actor->scale.z;
    scale.data[3][3] = 1.0f;
    return (scale);
}

static t_mat4f  calculate_matrix_rotation(const t_actor *actor)
{
    t_mat4f rotation;
    t_vec3f s;
    t_vec3f c;

    c.x = cosf(actor->orientation.x * (M_PI / 180.0f));
    c.y = cosf(actor->orientation.y * (M_PI / 180.0f));
    c.z = cosf(actor->orientation.z * (M_PI / 180.0f));
    s.x = sinf(actor->orientation.x * (M_PI / 180.0f));
    s.y = sinf(actor->orientation.y * (M_PI / 180.0f));
    s.z = sinf(actor->orientation.z * (M_PI / 180.0f));
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

static t_mat4f  calculate_matrix_translation(const t_actor *actor)
{
    t_mat4f translation;

    translation = mat4f_identity();
    translation.data[0][3] = actor->position.x;
    translation.data[1][3] = actor->position.y;
    translation.data[2][3] = actor->position.z;
    return (translation);
}

t_mat4f         actor_calculate_model_matrix(const t_actor *actor)
{
    t_mat4f scale;
    t_mat4f rotation;
    t_mat4f translation;
    t_mat4f sr;

    scale = calculate_matrix_scale(actor);
    rotation = calculate_matrix_rotation(actor);
    translation = calculate_matrix_translation(actor);
    sr = mat4f_mat4f_mult(&scale, &rotation);
    return (mat4f_mat4f_mult(&sr, &translation));
}
