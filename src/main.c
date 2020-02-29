/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <glad/glad.h>
#include "ft.h"
#include "objparser/objparser.h"
#include "input/input.h"
#include "renderer/renderer.h"
#include <stdlib.h>
#include "stdio.h"
#include <assert.h>
#include <time.h>

#ifdef WIN32
# undef main
#endif

float g_dt;
t_bool g_IsRunning;

#ifdef WIN32
char* ft_read_file(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (!file)
    {
        return (NULL);
    }

    t_byte* buffer = NULL;

    t_byte temp[4096 + 1];
    size_t size = 0;
    size_t ret;
    while ((ret = fread(temp, sizeof(t_byte), 4096, file)) != 0)
    {
        if (ferror(file))
        {
            free(buffer);
            fclose(file);
            return (NULL);
        }

        buffer = realloc(buffer, size + ret + 1);
        if (!buffer)
        {
            free(buffer);
            fclose(file);
            return (NULL);
        }
        ft_memcpy(buffer + size, temp, ret);
        size += ret;
        buffer[size] = '\0';

        if (feof(file))
        {
            break;
        }
    }

    fclose(file);
    return (buffer);
}
#endif

static void poll_events(t_scene_interactor *interactor)
{
    SDL_Event eventBuffer[4];
    SDL_PumpEvents();
    while (TRUE)
    {
        const int eventsCount = SDL_PeepEvents(eventBuffer,
                                               sizeof(eventBuffer) / sizeof(eventBuffer[0]),
                                               SDL_GETEVENT,
                                               SDL_FIRSTEVENT,
                                               SDL_LASTEVENT);
        if (eventsCount <= 0)
        {
            if (eventsCount < 0)
            {
                perror("SDL event handling error");
                g_IsRunning = FALSE;
            }

            break;
        }

        for (int index = 0; index < eventsCount; ++index)
        {
            SDL_Event* event = &eventBuffer[index];
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
                g_IsRunning = FALSE;
            } break;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    srand(time(NULL)); // just for rofl

    if (argc <= 1)
    {
        perror("Incorrect number of arguments");
        return (-1);
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        perror("Couldn't initialize SDL");
        return (-1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

    SDL_Window* win = SDL_CreateWindow("Scop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_SZ_X, WIN_SZ_Y, SDL_WINDOW_OPENGL);
	if (!win)
		return (-1);

    SDL_GLContext* glctx = SDL_GL_CreateContext(win);
	if (!glctx)
		return (-1);

    gladLoadGL();

    if (!renderer_init(&g_gfx_ctx))
    {
        assert("ERROR");
        // TODO: release resources
        return (-1);
    }

    t_scene scene;
    if (!scene_init(&scene, argv[1]))
    {
        // TODO: delete resources
        return (-1);
    }

    t_scene_interactor interactor = input_interactor_init(&scene);
    if (!renderer_init_gfx_interactor(&interactor))
    {
        assert("ERROR");
        // TODO: release resources
        return (-1);
    }
    input_interactor_select_actor(&interactor, &scene.actor);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.227f, 0.227f, 0.227f, 1.0f);

    Uint64	freq = SDL_GetPerformanceFrequency();
    Uint64	start;
    float elapsed_time = 0.0f;
    g_IsRunning = TRUE;
    while (g_IsRunning)
    {
        input_handle(&interactor);
        poll_events(&interactor);

        // tick

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        start = SDL_GetPerformanceCounter();

        // TODO: update vbos
        // glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, this->m_size * sizeof(T), (void*)this->m_data)

        renderer_draw_scene(&scene);
        renderer_draw_interactor(&interactor);

        SDL_GL_SwapWindow(win);
        g_dt = (SDL_GetPerformanceCounter() - start) / (float)freq;
        elapsed_time += g_dt;
    }

    scene_delete(&scene);
    renderer_delete_gfx_interactor(&interactor);
    renderer_delete(&g_gfx_ctx);

    SDL_GL_DeleteContext(glctx);
    SDL_DestroyWindow(win);
    SDL_Quit();

    // TODO: check system("leaks")
    return (0);
}
