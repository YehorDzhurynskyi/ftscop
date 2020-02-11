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
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "camera.h"

#ifdef WIN32
# undef main
#endif

t_camera g_camera;
t_vec3f g_POI;
float g_camera_distance = 1.0f;
float g_dt;
t_bool g_IsRunning;

static t_bool load_obj(const t_byte* buffer, const size_t size, t_mesh* out_mesh)
{
    // TODO: read http://paulbourke.net/dataformats/obj/
    t_parsing_ctx ctx;

    // TODO: remove magic
    out_mesh->vertices = malloc(sizeof(t_vec4f) * 256);
    out_mesh->colors = malloc(sizeof(t_vec4f) * 256);
    out_mesh->nvertices = 0;
    out_mesh->faces3 = malloc(sizeof(int) * 3 * 256);
    out_mesh->nfaces3 = 0;

    ctx.current = buffer;
    ctx.end = &buffer[size];
    ctx.total_size = size;
    while (ctx.current < ctx.end)
    {
        _parsing_skip_ws(&ctx);
        if (ctx.current >= ctx.end)
        {
            break;
        }

        const t_byte ch = ctx.current[0];
        if (ch == 'o' || ch == 'g' || ch == '#')
        {
            // TODO: handle 'o' and 'g' params
            _parsing_skip_until_nl(&ctx);
        }
        else if (ch == 's')
        {
            ctx.current++;
            _parsing_skip_ws(&ctx);

            if (_parsing_skip_if_match(&ctx, "off", sizeof("off") - 1) ||
                _parsing_skip_if_match(&ctx, "0", sizeof("0") - 1))
            {
                // TODO: turn off smooth shading
            }
            else if (_parsing_skip_if_match(&ctx, "on", sizeof("on") - 1) ||
                     _parsing_skip_if_match(&ctx, "1", sizeof("1") - 1))
            {
                // TODO: turn on smooth shading
            }
            else
            {
                assert(!"Error case");
                return (FALSE);
            }
        }
        else if (ch == 'f')
        {
            // TODO: test cases "f 4 3 1 {EOF}", "f 4 3 1{EOF}"

            ctx.current++;
            _parsing_skip_ws(&ctx);

            int face[4];
            int index = 0;
            while (ctx.current < ctx.end && ft_isdigit(*ctx.current))
            {
                const int vertexid = _parsing_read_int(&ctx);
                assert(vertexid > 0); // TODO: handle negative values
                face[index++] = vertexid - 1;
            }

            assert(index == 3 || index == 4);
            if (index == 3)
            {
                ft_memcpy(out_mesh->faces3 + 3 * out_mesh->nfaces3++, face, sizeof(int) * 3);
            }
            else if (index == 4)
            {
                ft_memcpy(out_mesh->faces3 + 3 * out_mesh->nfaces3++, face, sizeof(int) * 3);
                int temp[] = { face[2], face[3], face[0] };
                ft_memcpy(out_mesh->faces3 + 3 * out_mesh->nfaces3++, temp, sizeof(int) * 3);
            }
            else
            {
                // NOTE: convert to triangles to handle > 4 faces
                assert(!"Unhandled case"); // TODO: handle
            }
        }
        else if (ch == 'l')
        {
            assert(!"Unhandled case"); // TODO: handle
        }
        else if (ch == 'p')
        {
            assert(!"Unhandled case"); // TODO: handle
        }
        else if (ch == 'v')
        {
            if (ctx.current[1] == 't') // textures
            {
                assert(!"Unhandled case"); // TODO: handle
            }
            else if (ctx.current[1] == 'n') // normals
            {
                assert(!"Unhandled case"); // TODO: handle
            }
            else if (ctx.current[1] == 'p') // free-form geometry
            {
                assert(!"Unhandled case"); // TODO: handle
            }
            else
            {
                ctx.current++;

                out_mesh->vertices[out_mesh->nvertices].x = _parsing_read_float(&ctx);
                out_mesh->vertices[out_mesh->nvertices].y = _parsing_read_float(&ctx);
                out_mesh->vertices[out_mesh->nvertices].z = _parsing_read_float(&ctx);
#if 1
                // TODO: handle optional W coord
                out_mesh->vertices[out_mesh->nvertices].w = 1.0;
#else
                out_mesh->vertices[out_mesh->nvertices].w = _parsing_read_float(&ctx);
#endif
                // TODO: could be followed by a color in r, g, b [0.0 - 1.0] format
                out_mesh->colors[out_mesh->nvertices] = (t_vec4f) {rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1.0f};

                out_mesh->nvertices++;
            }
        }
        else
        {
            if (_parsing_skip_if_match(&ctx, "mtllib", sizeof("mtllib") - 1))
            {
                // TODO: load material
                _parsing_skip_until_nl(&ctx);
            }
            else if (_parsing_skip_if_match(&ctx, "usemtl", sizeof("usemtl") - 1))
            {
                // TODO: assign material
                _parsing_skip_until_nl(&ctx);
            }
            else
            {
                assert(!"Unhandled case"); // TODO: handle
            }
        }
    }
    return (TRUE);
}

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
    t_bool result = load_obj(buffer, ft_strlen(buffer), out_mesh);

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

    cam.fov = 90.0f;
    cam.ar = g_win_width / (float)g_win_height;
    cam.near = 0.1f;
    cam.far = 100.0f;
    cam.up = (t_vec3f) {0.0f, 1.0f, 0.0f};
    cam.look_at = g_POI;
    cam.position = (t_vec3f) {0.0f, 0.0f, 1.0f};

    return (cam);
}

GLuint shader_create_program(const char* vert_code, const char* frag_code);

int main(int argc, char* argv[])
{
    srand(time(NULL)); // just for rofl

    g_POI = (t_vec3f) { 0.0f, 0.0f, 0.0f };

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
    GLint view_projection_location = glGetUniformLocation(program_id, "u_view_projection");

    g_camera = create_default_camera();

    t_mesh mesh;
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
        poll_events();

        // tick

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        start = SDL_GetPerformanceCounter();

        // TODO: update vbos
        // glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, this->m_size * sizeof(T), (void*)this->m_data)

        glUseProgram(program_id);

        glBindVertexArray(vao);

        g_camera.position.x = sin(10.0f * elapsed_time) * g_camera_distance;
        g_camera.position.z = cos(10.0f * elapsed_time) * g_camera_distance;
        t_vec3f toeye = vec3f_sub(&g_camera.position, &g_POI);
        toeye = vec3f_normalize(&toeye);
        g_camera.position = vec3f_scalar(&toeye, g_camera_distance);
        t_mat4f view = camera_calculate_view_matrix(&g_camera);
        t_mat4f proj = camera_calculate_proj_matrix(&g_camera);
        t_mat4f vp = mat4f_mat4f_mult(&view, &proj);
        glUniformMatrix4fv(view_projection_location, 1, GL_FALSE, &vp.data[0][0]);

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
