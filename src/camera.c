/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

#define _USE_MATH_DEFINES // TODO: remove
#include <math.h>

t_mat4f camera_calculate_view_matrix(const t_camera* cam)
{
    t_mat4f view;
    t_vec3f forward;
    t_vec3f side;
    t_vec3f up;

    forward = vec3f_sub(&cam->look_at, &cam->position);
    forward = vec3f_normalize(&forward);
    side = vec3f_cross(&forward, &cam->up);
    side = vec3f_normalize(&side);
    up = vec3f_cross(&side, &forward);

    view = mat4f_identity();
    view.data[0][0] = side.x;
    view.data[1][0] = side.y;
    view.data[2][0] = side.z;
    view.data[0][1] = up.x;
    view.data[1][1] = up.y;
    view.data[2][1] = up.z;
    view.data[0][2] = -forward.x;
    view.data[1][2] = -forward.y;
    view.data[2][2] = -forward.z;
    view.data[3][0] = -vec3f_dot(&cam->position, &side);
    view.data[3][1] = -vec3f_dot(&cam->position, &up);
    view.data[3][2] = vec3f_dot(&cam->position, &forward);

    return (view);
}

t_mat4f camera_calculate_proj_matrix(const t_camera* cam)
{
    t_mat4f proj;
    float   slope;

    proj = mat4f_identity();
    slope = tan((cam->fov / 2.0f) * (M_PI / 180.0f));
    proj.data[0][0] = 1.0f / (cam->ar * slope);
    proj.data[1][1] = 1.0f / slope;
    proj.data[2][2] = -(cam->far + cam->near) / (cam->far - cam->near);
    proj.data[3][3] = 0.0f;
    proj.data[2][3] = -1.0f;
    proj.data[3][2] = -(2.0f * cam->far * cam->near) / (cam->far - cam->near);

    return (proj);
}
