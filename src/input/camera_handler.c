/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene.h"
#include <SDL.h>
#include <math.h>

#define CAM_SPEED		0.3
#define CAM_ROT_SPEED	1.5

static t_vec3f		rodrigoues_rotation(const t_vec3f *v,
const t_vec3f *n, const float angle)
{
	t_vec3f a;
	t_vec3f b;
	t_vec3f c;

	a = vec3f_scalar(n, vec3f_dot(v, n) * (1.0 - cos(angle)));
	b = vec3f_scalar(v, cos(angle));
	c = vec3f_cross(n, v);
	c = vec3f_scalar(&c, sin(angle));
	a = vec3f_add(&a, &b);
	return (vec3f_add(&a, &c));
}

static t_mat4f	camera_rotate(const Uint8 *keystate, t_vec3f *forward,
t_vec3f *right, t_vec3f *up)
{
	float	angle;

	if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_DOWN])
	{
		angle = CAM_ROT_SPEED * M_PI / 180.0;
		angle = keystate[SDL_SCANCODE_UP] ? angle : -angle;
		*up = rodrigoues_rotation(up, right, angle);
		*forward = rodrigoues_rotation(forward, right, angle);
	}
	if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT])
	{
		angle = CAM_ROT_SPEED * M_PI / 180.0;
		angle = keystate[SDL_SCANCODE_LEFT] ? angle : -angle;
		*right = rodrigoues_rotation(right, up, angle);
		*forward = rodrigoues_rotation(forward, up, angle);
	}
	if (keystate[SDL_SCANCODE_Q] || keystate[SDL_SCANCODE_E])
	{
		angle = CAM_ROT_SPEED * M_PI / 180.0;
		angle = keystate[SDL_SCANCODE_E] ? angle : -angle;
		*up = rodrigoues_rotation(up, forward, angle);
		*right = rodrigoues_rotation(right, forward, angle);
	}
	return (calculate_matrix_orientation_from_basis(right, up, forward));
}

void				input_handle_camera(t_camera *cam)
{
	const Uint8	*keystate;
	t_vec3f		translation;
	t_vec3f		right;
	t_vec3f		up;
	t_vec3f		forward;

	keystate = SDL_GetKeyboardState(NULL);
    calculate_basis_from_orientation(&cam->orientation, &right, &up, &forward);
	if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_DOWN]
	|| keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT]
	|| keystate[SDL_SCANCODE_Q] || keystate[SDL_SCANCODE_E])
		cam->orientation = camera_rotate(keystate, &forward, &right, &up);
	if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_S]
	|| keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D])
	{
        t_vec3f dpos;

        dpos = (t_vec3f) { 0.0, 0.0, 0.0 };

        if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_S])
            dpos.z = keystate[SDL_SCANCODE_W] ? CAM_SPEED : -CAM_SPEED;

        if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D])
            dpos.x = keystate[SDL_SCANCODE_A] ? -CAM_SPEED : CAM_SPEED;

        translation = transform_translate(&cam->orientation, &dpos);
		cam->position.x += translation.x;
		cam->position.y += translation.y;
		cam->position.z += translation.z;
	}
}
