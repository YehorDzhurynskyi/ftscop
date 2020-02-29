/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"
#include "renderer/renderer.h"

static t_bool   app_init_window(t_app* app)
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
    app->win = SDL_CreateWindow("scop 42",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                WIN_SZ_X,
                                WIN_SZ_Y,
                                SDL_WINDOW_OPENGL);
    return !!app->win;
}

t_bool          app_init(t_app* app)
{
    ft_memset(app, 0x0, sizeof(t_app));
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return (FALSE);
    }
    if (!app_init_window(app))
    {
        app_delete(app);
        return (FALSE);
    }
    app->glctx = SDL_GL_CreateContext(app->win);
    if (!app->glctx)
    {
        app_delete(app);
        return (FALSE);
    }
    return (TRUE);
}

void            app_delete(t_app* app)
{
    if (app->glctx)
    {
        SDL_GL_DeleteContext(app->glctx);
    }
    if (app->win)
    {
        SDL_DestroyWindow(app->win);
    }
    SDL_Quit();
}

void            app_loop(t_app* app, t_scene *scene, t_scene_interactor *interactor)
{
    Uint64	start;
    Uint64	freq;

    freq = SDL_GetPerformanceFrequency();
    app->is_running = TRUE;
    while (app->is_running)
    {
        start = SDL_GetPerformanceCounter();
        input_handle(interactor);
        app_poll_events(app, interactor);
        scene_update(scene, app->delta_time);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderer_draw_scene(scene);
        renderer_draw_interactor(interactor);
        SDL_GL_SwapWindow(app->win);
        app->delta_time = (SDL_GetPerformanceCounter() - start) / (float)freq;
    }
}
