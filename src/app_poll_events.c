/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_poll_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

static void process_event(SDL_Event* event, t_app* app, t_scene_interactor* interactor)
{
    t_actor* a;

    a = interactor->actor_selected;
    if (event->type == SDL_KEYDOWN)
    {
        if (interactor->actor_selected != NULL)
        {
            if (event->key.keysym.sym == SDLK_z)
                actor_palette_set(a, (a->material.palette + 1) % Palette_COUNT);
            else if (event->key.keysym.sym == SDLK_f)
                a->material.smooth = !a->material.smooth;
            else if (event->key.keysym.sym == SDLK_g)
                a->material.grayscale = !a->material.grayscale;
            else if (event->key.keysym.sym == SDLK_h)
                a->material.wireframe = !a->material.wireframe;
        }
        else if (event->key.keysym.sym == SDLK_LEFTBRACKET ||
                 event->key.keysym.sym == SDLK_RIGHTBRACKET)
            interactor->actor_selected = &interactor->scene_target->actor;
    }
    else if (event->type == SDL_QUIT)
        app->is_running = FALSE;
}

void        app_poll_events(t_app* app, t_scene_interactor* interactor)
{
    SDL_Event   event_buffer[4];
    int         event_count;
    int         i;

    SDL_PumpEvents();
    while (TRUE)
    {
        event_count = SDL_PeepEvents(event_buffer,
                                     sizeof(event_buffer) / sizeof(event_buffer[0]),
                                     SDL_GETEVENT,
                                     SDL_FIRSTEVENT,
                                     SDL_LASTEVENT);
        if (event_count <= 0)
            break;
        i = 0;
        while (i < event_count)
            process_event(&event_buffer[i++], app, interactor);
    }
    if (event_count < 0)
    {
        perror("SDL event handling error!");
        app->is_running = FALSE;
    }
}
