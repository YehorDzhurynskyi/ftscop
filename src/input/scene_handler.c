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
#include <SDL.h>
#include <math.h>
#include <assert.h>

#define ACTOR_SPEED		0.3
#define ACTOR_ROT_SPEED	1.5

void	input_handle(t_scene_interactor *interactor)
{
    const Uint8	*keystate;
    SDL_Keymod  mod;

    assert(interactor);
    assert(interactor->scene_target);
    mod = SDL_GetModState();
    keystate = SDL_GetKeyboardState(NULL);
    if (interactor->actor_selected)
    {
        if (keystate[SDL_SCANCODE_ESCAPE])
        {
            interactor->actor_selected = NULL;
        }
        else if (mod & KMOD_LCTRL)
        {
            if (keystate[SDL_SCANCODE_S])
            {
                interactor->interaction_mode = SCALING;
            }
            else if (keystate[SDL_SCANCODE_R])
            {
                interactor->interaction_mode = ROTATION;
            }
            else if (keystate[SDL_SCANCODE_T])
            {
                interactor->interaction_mode = TRANSLATION;
            }
        }
        else if (keystate[SDL_SCANCODE_1] || keystate[SDL_SCANCODE_2] ||
                 keystate[SDL_SCANCODE_3] || keystate[SDL_SCANCODE_4] || 
                 keystate[SDL_SCANCODE_5] || keystate[SDL_SCANCODE_6])
        {
            if (interactor->interaction_mode == TRANSLATION)
            {
                t_vec3f dpos;

                dpos = (t_vec3f) { 0.0, 0.0, 0.0 };
                if (keystate[SDL_SCANCODE_1] || keystate[SDL_SCANCODE_2])
                    dpos.x = keystate[SDL_SCANCODE_1] ? ACTOR_SPEED : -ACTOR_SPEED;

                if (keystate[SDL_SCANCODE_3] || keystate[SDL_SCANCODE_4])
                    dpos.y = keystate[SDL_SCANCODE_3] ? -ACTOR_SPEED : ACTOR_SPEED;

                if (keystate[SDL_SCANCODE_5] || keystate[SDL_SCANCODE_6])
                    dpos.z = keystate[SDL_SCANCODE_5] ? -ACTOR_SPEED : ACTOR_SPEED;

                // TODO: create option to translate locally and globally

                t_vec3f translation;
                translation = transform_translate(&interactor->actor_selected->orientation, &dpos);
                interactor->actor_selected->position = vec3f_add(&interactor->actor_selected->position, &translation);
            }
            else if (interactor->interaction_mode == ROTATION)
            {
                t_vec3f drot;

                drot = (t_vec3f) { 0.0, 0.0, 0.0 };
                if (keystate[SDL_SCANCODE_1] || keystate[SDL_SCANCODE_2])
                {
                    drot.x = ACTOR_ROT_SPEED * M_PI / 180.0;
                    drot.x = keystate[SDL_SCANCODE_1] ? drot.x : -drot.x;
                }
                if (keystate[SDL_SCANCODE_3] || keystate[SDL_SCANCODE_4])
                {
                    drot.y = ACTOR_ROT_SPEED * M_PI / 180.0;
                    drot.y = keystate[SDL_SCANCODE_3] ? drot.y : -drot.y;
                }
                if (keystate[SDL_SCANCODE_5] || keystate[SDL_SCANCODE_6])
                {
                    drot.z = ACTOR_ROT_SPEED * M_PI / 180.0;
                    drot.z = keystate[SDL_SCANCODE_5] ? drot.z : -drot.z;
                }
                interactor->actor_selected->orientation = transform_rotate(&interactor->actor_selected->orientation, &drot);
            }
        }
    }
    input_handle_camera(&interactor->scene_target->camera);
}
