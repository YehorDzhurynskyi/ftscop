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
#define CAM_ROT_SPEED	2.0

void	input_handle_camera(t_camera *cam)
{
	const Uint8	*keystate;
	t_vec3f		translation;

	keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_DOWN] ||
        keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT] ||
        keystate[SDL_SCANCODE_Q] || keystate[SDL_SCANCODE_E])
    {
        t_vec3f drot;

        drot = (t_vec3f) { 0.0, 0.0, 0.0 };
        if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_DOWN])
        {
            drot.x = CAM_ROT_SPEED * M_PI / 180.0;
            drot.x = keystate[SDL_SCANCODE_UP] ? drot.x : -drot.x;
        }
        if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT])
        {
            drot.y = CAM_ROT_SPEED * M_PI / 180.0;
            drot.y = keystate[SDL_SCANCODE_LEFT] ? drot.y : -drot.y;
        }
        if (keystate[SDL_SCANCODE_Q] || keystate[SDL_SCANCODE_E])
        {
            drot.z = CAM_ROT_SPEED * M_PI / 180.0;
            drot.z = keystate[SDL_SCANCODE_E] ? drot.z : -drot.z;
        }
        cam->orientation = transform_rotate(&cam->orientation, &drot);
    }

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
        cam->position = vec3f_add(&cam->position, &translation);
	}
}
