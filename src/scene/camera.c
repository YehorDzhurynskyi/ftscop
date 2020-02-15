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

#define _USE_MATH_DEFINES // TODO: remove
#include <math.h>
#include "scene.h"

void	camera_look_at(t_camera *cam, const t_vec3f *pos,
const t_vec3f *poi, const t_vec3f *up)
{
	t_vec3f		forward;
	t_vec3f		right;
	t_vec3f		nup;

	cam->position = *pos;
	nup = vec3f_normalize(up);
	forward = vec3f_sub(poi, pos);
	forward = vec3f_normalize(&forward);
	right = vec3f_cross(&forward, &nup);
	right = vec3f_normalize(&right);
	nup = vec3f_cross(&right, &forward);
	nup = vec3f_normalize(&nup);
    forward = vec3f_scalar(&forward, -1.0f);
	cam->orientation = calculate_matrix_orientation_from_basis(&right, &nup, &forward);
    cam->orientation = mat4f_transpose(&cam->orientation);
}

t_mat4f camera_calculate_matrix_view(const t_camera* cam)
{
    t_mat4f view;
    t_vec3f backward;
    t_vec3f side;
    t_vec3f up;

    side = (t_vec3f)
    {
        cam->orientation.data[0][0],
        cam->orientation.data[1][0],
        cam->orientation.data[2][0]
    };
    up = (t_vec3f)
    {
        cam->orientation.data[0][1],
        cam->orientation.data[1][1],
        cam->orientation.data[2][1]
    };
    backward = (t_vec3f)
    {
        cam->orientation.data[0][2],
        cam->orientation.data[1][2],
        cam->orientation.data[2][2]
    };

    view = mat4f_identity();
    view = mat4f_mat4f_mult(&view, &cam->orientation);
    view.data[3][0] = -vec3f_dot(&cam->position, &side);
    view.data[3][1] = -vec3f_dot(&cam->position, &up);
    view.data[3][2] = -vec3f_dot(&cam->position, &backward);

    return (view);
}

t_mat4f camera_calculate_matrix_proj(const t_camera* cam)
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
