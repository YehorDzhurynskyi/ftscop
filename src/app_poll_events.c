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

static void process_event(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
    {
        if (event->key.state == SDL_PRESSED)
        {
            switch (event->key.keysym.sym)
            {
            case SDLK_LEFTBRACKET:
            {
                if (interactor->actor_selected == NULL)
                {
                    interactor->actor_selected = &interactor->scene_target->actor;
                }
            } break;
            case SDLK_RIGHTBRACKET:
            {
                if (interactor->actor_selected == NULL)
                {
                    interactor->actor_selected = &interactor->scene_target->actor;
                }
            } break;
            case SDLK_z:
            {
                if (interactor->actor_selected != NULL)
                {
                    const t_palette next_palette = (interactor->actor_selected->material.palette + 1) % Palette_COUNT;
                    actor_palette_set(interactor->actor_selected, next_palette);
                }
            } break;
            case SDLK_h:
            {
                if (interactor->actor_selected != NULL)
                {
                    interactor->actor_selected->material.wireframe = !interactor->actor_selected->material.wireframe;
                }
            } break;
            case SDLK_g:
            {
                if (interactor->actor_selected != NULL)
                {
                    interactor->actor_selected->material.grayscale = !interactor->actor_selected->material.grayscale;
                }
            } break;
            case SDLK_f:
            {
                if (interactor->actor_selected != NULL)
                {
                    interactor->actor_selected->material.smooth = !interactor->actor_selected->material.smooth;
                }
            } break;
            }
        }
    } break;
    case SDL_QUIT:
    {
        // TODO: it doesn't work properly
        // X or alt+f4 don't work
        app->is_running = FALSE;
    } break;
    }
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
            process_event(&event_buffer[i++]);
    }
    if (event_count < 0)
    {
        perror("SDL event handling error!");
        app->is_running = FALSE;
    }
}
