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
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#ifdef WIN32
# undef main
#endif

float g_dt;
t_bool g_IsRunning;

#ifdef WIN32
char* ft_read_file(const char* filename)
{
    FILE* file = fopen(filename, "r");

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

static t_bool load_obj_file(const char* filename, t_mesh* out_mesh)
{
    t_byte* buffer;

    buffer = ft_read_file(filename);
    t_bool result = objparser_parse_mesh(buffer, ft_strlen(buffer), out_mesh);
    free(buffer);

    if (result)
    {
        // TODO: recalculate origin for a mesh
    }

    return (result);
}

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
                            interactor->actor_selected = interactor->scene_target->actors;
                        }
                    } break;
                    case SDLK_RIGHTBRACKET:
                    {
                        if (interactor->actor_selected == NULL)
                        {
                            interactor->actor_selected = interactor->scene_target->actors;
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

const int g_win_width = 800;
const int g_win_height = 600;

static t_camera create_default_camera()
{
    t_camera cam;

    t_vec3f pos = (t_vec3f){ 5.0f, 5.0f, 5.0f }; // TODO: set pos according to maximum radius of input meshes
    t_vec3f poi = (t_vec3f){ 0.0f, 0.0f, 0.0f };
    t_vec3f up = (t_vec3f){0.0f, 1.0f, 0.0f};

    camera_look_at(&cam, &pos, &poi, &up);
    cam.fov = 90.0f;
    cam.ar = g_win_width / (float)g_win_height;
    cam.near = 0.1f;
    cam.far = 100.0f;

    return (cam);
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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

    SDL_Window* win = SDL_CreateWindow("Scop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, g_win_width, g_win_height, SDL_WINDOW_OPENGL);
    SDL_GLContext* glctx = SDL_GL_CreateContext(win);

    gladLoadGL();

    if (!renderer_init(&g_gfx_ctx))
    {
        assert("ERROR");
        // TODO: release resources
        return (-1);
    }

    t_mesh mesh;
    mesh = mesh_init();

    // TODO: remove magic
    mesh.vertices = malloc(sizeof(t_vec4f) * 256);
    mesh.colors = malloc(sizeof(t_vec4f) * 256);
    mesh.nvertices = 0;
    mesh.faces = malloc(sizeof(int) * 3 * 256);
    mesh.nfaces = 0;

    if ((g_IsRunning = load_obj_file(argv[1], &mesh)) != TRUE)
    {
        perror("Invalid input file");
        return (-1);
    }

    const t_bool res = renderer_init_gfx_mesh(&mesh);

    FT_SAFE_FREE(mesh.faces);
    FT_SAFE_FREE(mesh.vertices);
    FT_SAFE_FREE(mesh.colors);

    if (!res)
    {
        assert("ERROR");
        // TODO: release resources
        return (-1);
    }

    t_scene scene;
    {
        // TODO: create abstraction for scene creation

        scene.camera = create_default_camera();

        scene.actors = malloc(sizeof(t_actor) * 10);
        scene.nactors = 1;

        scene.meshes = malloc(sizeof(t_mesh) * 10);
        scene.nmeshes = 1;

        scene.materials = malloc(sizeof(t_material) * 10);
        scene.nmaterials = 0;

        memcpy(scene.meshes, &mesh, sizeof(t_mesh));

        t_actor actor;
        actor.material = NULL;
        actor.mesh = scene.meshes;
        actor.position = (t_vec3f) { 0.0f, 0.0f, 0.0f };
        actor.orientation = mat4f_identity();
        actor.scale = (t_vec3f) { 1.0f, 1.0f, 1.0f };

        memcpy(scene.actors, &actor, sizeof(t_actor));
    }

    t_scene_interactor interactor = input_interactor_init(&scene);
    if (!renderer_init_gfx_interactor(&interactor))
    {
        assert("ERROR");
        // TODO: release resources
        return (-1);
    }
    input_interactor_select_actor(&interactor, scene.actors);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.227f, 0.227f, 0.227f, 1.0f);

    Uint64	freq = SDL_GetPerformanceFrequency();
    Uint64	start;
    float elapsed_time = 0.0f;
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
    return (0);
}
