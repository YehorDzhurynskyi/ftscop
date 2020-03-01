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

#include "app.h"
#include "renderer/renderer.h"

#ifdef WIN32
#undef main
#include "stdio.h"
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

static t_bool   startup(t_app *app,
                        t_scene *scene,
                        t_scene_interactor *interactor,
                        const char *filename)
{
    if (app_init(app))
    {
        if (gladLoadGL() && renderer_init(&g_gfx_ctx))
        {
            if (scene_init(scene, filename))
            {
                if (scene_interactor_init(interactor, scene))
                {
                    srand(time(NULL));
                    glEnable(GL_DEPTH_TEST);
                    glDepthFunc(GL_LESS);
                    glClearColor(0.227f, 0.227f, 0.227f, 1.0f);
                    return (TRUE);
                }
                scene_delete(scene);
            }
            renderer_delete(&g_gfx_ctx);
        }
        app_delete(app);
    }
    return (FALSE);
}

static void     shutdown(t_app* app,
                         t_scene* scene,
                         t_scene_interactor* interactor)
{
    scene_interactor_delete(interactor);
    scene_delete(scene);
    renderer_delete(&g_gfx_ctx);
    app_delete(app);
}

int scopmain(int argc, char* argv[])
{
    t_app               app;
    t_scene             scene;
    t_scene_interactor  interactor;

    if (argc <= 1)
    {
        perror("Incorrect number of arguments!");
        return (-1);
    }
    if (!startup(&app, &scene, &interactor, argv[1]))
    {
        perror("Application error on startup!");
        return (-1);
    }
    app_loop(&app, &scene, &interactor);
    shutdown(&app, &scene, &interactor);
    // TODO: check system("leaks")
    return (0);
}
