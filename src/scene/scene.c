/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "renderer/renderer.h"

t_bool  scene_init(t_scene* scene, const char *objfile)
{
    t_bool      result;
    t_texture   t;

    if (mesh_load_objfile(objfile, &scene->mesh) == FALSE)
    {
        return (FALSE);
    }
    if (!texture_load_bmp("squidward.bmp", &t))
    {
        // TODO: test error path
        // TODO: print error
        mesh_delete(&scene->mesh);
        return (FALSE);
    }
    actor_init(&scene->actor, &scene->mesh, &t);
    texture_delete(&t);
    scene_camera_reset(scene);
    return (TRUE);
}

void    scene_delete(t_scene *scene)
{
    mesh_delete(&scene->mesh);
    actor_delete(&scene->actor);
}

void    scene_camera_reset(t_scene *scene)
{
    t_vec3f pos = (t_vec3f){ 5.0f, 5.0f, 5.0f }; // TODO: set pos according to maximum radius of input meshes
    t_vec3f poi = (t_vec3f){ 0.0f, 0.0f, 0.0f };
    t_vec3f up = (t_vec3f){ 0.0f, 1.0f, 0.0f };

    camera_look_at(&scene->camera, &pos, &poi, &up);
    scene->camera.fov = 90.0f;
    scene->camera.ar = WIN_SZ_X / (float)WIN_SZ_Y;
    scene->camera.near = 0.1f;
    scene->camera.far = 100.0f;
}
