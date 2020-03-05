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
#include "app.h"

#define CAM_SPEED		10.0f
#define CAM_ROT_SPEED	60.0f

static void	camera_translate(t_app *app, t_camera *cam, const Uint8 *keystate)
{
	t_vec3f dpos;

	dpos = (t_vec3f){ 0.0, 0.0, 0.0 };
	if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_S])
		dpos.z = keystate[SDL_SCANCODE_W] ? -CAM_SPEED : CAM_SPEED;
	if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D])
		dpos.x = keystate[SDL_SCANCODE_A] ? -CAM_SPEED : CAM_SPEED;
	dpos = vec3f_scalar(&dpos, app->delta_time);
	dpos = transform_translate(&cam->orientation, &dpos);
	cam->position = vec3f_add(&cam->position, &dpos);
}

static void	camera_rotate(t_app *app, t_camera *cam, const Uint8 *keystate)
{
	t_vec3f drot;

	drot = (t_vec3f){ 0.0, 0.0, 0.0 };
	if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_DOWN])
	{
		drot.x = CAM_ROT_SPEED * M_PI / 180.0;
		drot.x = keystate[SDL_SCANCODE_UP] ? -drot.x : drot.x;
	}
	if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT])
	{
		drot.y = CAM_ROT_SPEED * M_PI / 180.0;
		drot.y = keystate[SDL_SCANCODE_LEFT] ? -drot.y : drot.y;
	}
	if (keystate[SDL_SCANCODE_Q] || keystate[SDL_SCANCODE_E])
	{
		drot.z = CAM_ROT_SPEED * M_PI / 180.0;
		drot.z = keystate[SDL_SCANCODE_E] ? drot.z : -drot.z;
	}
	drot = vec3f_scalar(&drot, app->delta_time);
	cam->orientation = transform_rotate(&cam->orientation, &drot);
}

void		input_handle_camera(t_app *app, t_camera *cam)
{
	const Uint8	*keystate;

	keystate = SDL_GetKeyboardState(NULL);
	if (SDL_GetModState() & KMOD_ALT)
	{
		return ;
	}
	if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_DOWN] ||
		keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT] ||
		keystate[SDL_SCANCODE_Q] || keystate[SDL_SCANCODE_E])
	{
		camera_rotate(app, cam, keystate);
	}
	if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_S] ||
		keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D])
	{
		camera_translate(app, cam, keystate);
	}
}
