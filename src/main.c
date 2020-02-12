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

    return (result);
}

static void poll_events()
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
#if 0
            case SDL_KEYDOWN:
            {
                if (event->key.state == SDL_PRESSED)
                {
                    switch (event->key.keysym.sym)
                    {
                    case SDLK_EQUALS:
                    case SDLK_PLUS:
                    case SDLK_KP_PLUS:
                    {
                        g_camera_distance -= 1.0f;
                        g_camera_distance = max(1.0f, g_camera_distance);
                    } break;
                    case SDLK_MINUS:
                    case SDLK_KP_MINUS:
                    {
                        g_camera_distance += 1.0f;
                        g_camera_distance = min(100.0f, g_camera_distance);
                    } break;
                    }
                }
            } break;
#endif
            case SDL_QUIT:
            {
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

    t_vec3f pos = (t_vec3f){ 0.0f, 0.0f, 1.0f };
    t_vec3f poi = (t_vec3f){ 0.0f, 0.0f, 0.0f };
    t_vec3f up = (t_vec3f){0.0f, 1.0f, 0.0f};

    camera_look_at(&cam, &pos, &poi, &up);
    cam.fov = 90.0f;
    cam.ar = g_win_width / (float)g_win_height;
    cam.near = 0.1f;
    cam.far = 100.0f;

    return (cam);
}

GLuint shader_create_program(const char* vert_code, const char* frag_code);

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

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_Window* win = SDL_CreateWindow("Scop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, g_win_width, g_win_height, SDL_WINDOW_OPENGL);
    SDL_GLContext* glctx = SDL_GL_CreateContext(win);

    gladLoadGL();

    const char* vert_code = ft_read_file("shaders/phong.vert");
    const char* frag_code = ft_read_file("shaders/phong.frag");

    if (!vert_code || !frag_code)
    {
        assert(!"Error");
        // TODO: free all resources
        free(vert_code);
        free(frag_code);
        return (-1);
    }

    GLuint program_id = shader_create_program(vert_code, frag_code);

    free(vert_code);
    free(frag_code);

    if (!program_id)
    {
        assert(!"Error");
        // TODO: free all resources
        return (-1);
    }

    GLint vertex_location = glGetAttribLocation(program_id, "a_position");
    GLint color_tint_location = glGetAttribLocation(program_id, "a_color_tint");
    GLint model_location = glGetUniformLocation(program_id, "u_model");
    GLint view_location = glGetUniformLocation(program_id, "u_view");
    GLint projection_location = glGetUniformLocation(program_id, "u_projection");

    t_mesh mesh;
    // TODO: remove magic
    mesh.vertices = malloc(sizeof(t_vec4f) * 256);
    mesh.colors = malloc(sizeof(t_vec4f) * 256);
    mesh.nvertices = 0;
    mesh.faces3 = malloc(sizeof(int) * 3 * 256);
    mesh.nfaces3 = 0;

#if 1
    if ((g_IsRunning = load_obj_file(argv[1], &mesh)) != TRUE)
    {
        perror("Invalid input file");
        return (-1);
    }
#else
    g_IsRunning = TRUE;
    mesh.nvertices = 4;

    mesh.vertices = malloc(sizeof(t_vec4f) * mesh.nvertices);
    t_vec4f vertices[] = {
        (t_vec4f) { 0.5f, 0.5f, 0.0f, 1.0f },
        (t_vec4f) { -0.5f, 0.5f, 0.0f, 1.0f },
        (t_vec4f) { 0.5f, -0.5f, 0.0f, 1.0f },
        (t_vec4f) { -0.5f, -0.5f, 0.0f, 1.0f }
    };
    memcpy(mesh.vertices, vertices, sizeof(t_vec4f) * mesh.nvertices);

    mesh.colors = malloc(sizeof(t_vec4f) * mesh.nvertices);
    t_vec4f colors[] = {
        (t_vec4f) { 1.0f, 1.0f, 1.0f, 1.0f },
        (t_vec4f) { 1.0f, 0.0f, 1.0f, 1.0f },
        (t_vec4f) { 1.0f, 1.0f, 0.0f, 1.0f },
        (t_vec4f) { 0.0f, 1.0f, 1.0f, 1.0f }
    };
    memcpy(mesh.colors, colors, sizeof(t_vec4f) * mesh.nvertices);

    mesh.nfaces3 = 2;
    mesh.faces3 = malloc(sizeof(int) * 3 * mesh.nfaces3);
    int indices[] = { 0, 1, 3, 3, 2, 0 };
    memcpy(mesh.faces3, indices, sizeof(int) * 3 * mesh.nfaces3);
#endif
    t_scene scene;
    t_scene_interactor interactor;
    interactor.scene_target = &scene;
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
        actor.rotation = (t_vec3f) { 0.0f, 0.0f, 0.0f };
        actor.scale = (t_vec3f) { 1.0f, 1.0f, 1.0f };

        memcpy(scene.actors, &actor, sizeof(t_actor));
    }
    interactor.actor_selected = scene.actors;

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint faces3_ibo;
    glGenBuffers(1, &faces3_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faces3_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.nfaces3 * 3 * sizeof(int), mesh.faces3, GL_STATIC_DRAW);

    GLuint vertex_vbo;
    glGenBuffers(1, &vertex_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.nvertices * sizeof(t_vec4f), mesh.vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertex_location);
    glVertexAttribPointer(vertex_location, 4, GL_FLOAT, GL_FALSE, 0/*sizeof(t_vec4f)*/, (void*)0);

    GLuint color_tint_vbo;
    glGenBuffers(1, &color_tint_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, color_tint_vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.nvertices * sizeof(t_vec4f), mesh.colors, GL_DYNAMIC_DRAW); // TODO: change color tint dynamically
    glEnableVertexAttribArray(color_tint_location);
    glVertexAttribPointer(color_tint_location, 4, GL_FLOAT, GL_FALSE, 0/*sizeof(t_vec4f)*/, (void*)0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.62f, 0.59f, 0.52f, 1.0f);

    Uint64	freq = SDL_GetPerformanceFrequency();
    Uint64	start;
    float elapsed_time = 0.0f;
    while (g_IsRunning)
    {
        input_handle(&interactor);
        poll_events();

        // tick

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        start = SDL_GetPerformanceCounter();

        // TODO: update vbos
        // glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, this->m_size * sizeof(T), (void*)this->m_data)

        glUseProgram(program_id);

        glBindVertexArray(vao);

#if 0
        g_camera.position.x = sin(10.0f * elapsed_time) * g_camera_distance;
        g_camera.position.z = cos(10.0f * elapsed_time) * g_camera_distance;
        t_vec3f toeye = vec3f_sub(&g_camera.position, &g_POI);
        toeye = vec3f_normalize(&toeye);
        g_camera.position = vec3f_scalar(&toeye, g_camera_distance);
        t_vec3f up = (t_vec3f){ 0.0f, 1.0f, 0.0f };
        camera_look_at(&g_camera, &g_camera.position, &g_POI, &up);
#endif

        //t_mat4f vp = mat4f_mat4f_mult(&view, &proj);

        t_mat4f model = actor_calculate_matrix_model(&scene.actors[0]);
        t_mat4f view = camera_calculate_matrix_view(&scene.camera);
        t_mat4f proj = camera_calculate_matrix_proj(&scene.camera);

        glUniformMatrix4fv(model_location, 1, GL_FALSE, &model.data[0][0]);
        glUniformMatrix4fv(view_location, 1, GL_FALSE, &view.data[0][0]);
        glUniformMatrix4fv(projection_location, 1, GL_FALSE, &proj.data[0][0]);

        glDrawElements(GL_TRIANGLES, mesh.nfaces3 * 3, GL_UNSIGNED_INT, NULL);

        SDL_GL_SwapWindow(win);
        g_dt = (SDL_GetPerformanceCounter() - start) / (float)freq;
        elapsed_time += g_dt;
    }

    glDeleteProgram(program_id);

    glDeleteBuffers(1, &vertex_vbo);
    glDeleteBuffers(1, &color_tint_vbo);
    glDeleteBuffers(1, &faces3_ibo);

    glDeleteVertexArrays(1, &vao);

    SDL_GL_DeleteContext(glctx);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return (0);
}
