/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "app.h"

#define ACTOR_SPEED		10.0f
#define ACTOR_ROT_SPEED	60.0f

static void	actor_translate(t_app *app, t_actor *actor, const Uint8 *keystate)
{
	t_vec3f dpos;

	dpos = (t_vec3f){ 0.0, 0.0, 0.0 };
	if (keystate[SDL_SCANCODE_1] || keystate[SDL_SCANCODE_2])
		dpos.x = keystate[SDL_SCANCODE_1] ? ACTOR_SPEED : -ACTOR_SPEED;
	if (keystate[SDL_SCANCODE_3] || keystate[SDL_SCANCODE_4])
		dpos.y = keystate[SDL_SCANCODE_3] ? -ACTOR_SPEED : ACTOR_SPEED;
	if (keystate[SDL_SCANCODE_5] || keystate[SDL_SCANCODE_6])
		dpos.z = keystate[SDL_SCANCODE_5] ? -ACTOR_SPEED : ACTOR_SPEED;
	dpos = vec3f_scalar(&dpos, app->delta_time);
	dpos = transform_translate(&actor->orientation, &dpos);
	actor->position = vec3f_add(&actor->position, &dpos);
}

static void	actor_rotate(t_app *app, t_actor *actor, const Uint8 *keystate)
{
	float	rot;

	rot = (app->delta_time * ACTOR_ROT_SPEED) * ((float)M_PI / 180.0f);
	if (keystate[SDL_SCANCODE_1] || keystate[SDL_SCANCODE_2])
	{
		rot = keystate[SDL_SCANCODE_1] ? rot : -rot;
		actor->orientation = transform_rotate_x(&actor->orientation, rot);
	}
	else if (keystate[SDL_SCANCODE_3] || keystate[SDL_SCANCODE_4])
	{
		rot = keystate[SDL_SCANCODE_3] ? rot : -rot;
		actor->orientation = transform_rotate_y(&actor->orientation, rot);
	}
	else if (keystate[SDL_SCANCODE_5] || keystate[SDL_SCANCODE_6])
	{
		rot = keystate[SDL_SCANCODE_5] ? rot : -rot;
		actor->orientation = transform_rotate_z(&actor->orientation, rot);
	}
}

static void	actor_scale(t_app *app, t_actor *actor, const Uint8 *keystate)
{
	t_vec3f dscale;

	dscale = (t_vec3f){ 0.0, 0.0, 0.0 };
	if (keystate[SDL_SCANCODE_1] || keystate[SDL_SCANCODE_2])
		dscale.x = keystate[SDL_SCANCODE_1] ? ACTOR_SPEED : -ACTOR_SPEED;
	if (keystate[SDL_SCANCODE_3] || keystate[SDL_SCANCODE_4])
		dscale.y = keystate[SDL_SCANCODE_3] ? -ACTOR_SPEED : ACTOR_SPEED;
	if (keystate[SDL_SCANCODE_5] || keystate[SDL_SCANCODE_6])
		dscale.z = keystate[SDL_SCANCODE_5] ? -ACTOR_SPEED : ACTOR_SPEED;
	dscale = vec3f_scalar(&dscale, app->delta_time);
	actor->scale = vec3f_add(&actor->scale, &dscale);
	actor->scale.x = FT_MAX(0.1f, actor->scale.x);
	actor->scale.y = FT_MAX(0.1f, actor->scale.y);
	actor->scale.z = FT_MAX(0.1f, actor->scale.z);
}

static void	actor_handle_transformation(t_app *app,
										t_scene_interactor *interactor,
										const Uint8 *keystate)
{
	if (keystate[SDL_SCANCODE_1] || keystate[SDL_SCANCODE_2] ||
		keystate[SDL_SCANCODE_3] || keystate[SDL_SCANCODE_4] ||
		keystate[SDL_SCANCODE_5] || keystate[SDL_SCANCODE_6])
	{
		if (interactor->interaction_mode == TRANSLATION)
			actor_translate(app, interactor->actor_selected, keystate);
		else if (interactor->interaction_mode == ROTATION)
			actor_rotate(app, interactor->actor_selected, keystate);
		else if (interactor->interaction_mode == SCALING)
			actor_scale(app, interactor->actor_selected, keystate);
	}
}

void		input_handle(t_app *app, t_scene_interactor *interactor)
{
	const Uint8	*keystate;
	SDL_Keymod	mod;

	mod = SDL_GetModState();
	keystate = SDL_GetKeyboardState(NULL);
	if (interactor->actor_selected)
	{
		if (keystate[SDL_SCANCODE_ESCAPE])
		{
			interactor->actor_selected = NULL;
		}
		else if (mod & KMOD_ALT)
		{
			if (keystate[SDL_SCANCODE_S])
				interactor->interaction_mode = SCALING;
			else if (keystate[SDL_SCANCODE_R])
				interactor->interaction_mode = ROTATION;
			else if (keystate[SDL_SCANCODE_T])
				interactor->interaction_mode = TRANSLATION;
		}
		actor_handle_transformation(app, interactor, keystate);
	}
	input_handle_camera(app, &interactor->scene_target->camera);
}
