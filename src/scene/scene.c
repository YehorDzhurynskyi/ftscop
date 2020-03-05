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

#include "app.h"
#include "renderer/renderer.h"

t_bool	scene_init(t_scene *scene, const char *objfile)
{
	t_texture	t;

	if (mesh_load_objfile(objfile, &scene->mesh) == FALSE)
	{
		perror("Mesh loading error!");
		return (FALSE);
	}
	if (!texture_load_bmp("squidward.bmp", &t))
	{
		perror("Texture loading error!");
		mesh_delete(&scene->mesh);
		return (FALSE);
	}
	actor_init(&scene->actor, &scene->mesh, &t);
	texture_delete(&t);
	scene_camera_reset(scene);
	return (TRUE);
}

void	scene_delete(t_scene *scene)
{
	mesh_delete(&scene->mesh);
	actor_delete(&scene->actor);
}

void	scene_camera_reset(t_scene *scene)
{
	t_vec3f	pos;
	t_vec3f	poi;
	t_vec3f	up;
	float	radius;

	radius = actor_radius_max_get(&scene->actor);
	pos = (t_vec3f) { radius, radius, radius };
	pos = vec3f_add(&pos, &scene->actor.position);
	poi = scene->actor.position;
	up = (t_vec3f) { 0.0f, 1.0f, 0.0f };
	camera_look_at(&scene->camera, &pos, &poi, &up);
	scene->camera.fov = 90.0f;
	scene->camera.ar = WIN_SZ_X / (float)WIN_SZ_Y;
	scene->camera.near = 0.1f;
	scene->camera.far = 100.0f;
}

void	scene_update(t_scene *scene, float dt)
{
	t_vec4f	*mapped;
	t_vec4f	color_diff;
	int		i;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scene->mesh.vbo_color);
	if ((mapped = (t_vec4f*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER,
	GL_READ_WRITE)) == NULL)
	{
		return ;
	}
	i = 0;
	while (i < (int)scene->mesh.nvertices)
	{
		color_diff = vec4f_sub(&scene->actor.material.color_target[i],
		&mapped[i]);
		color_diff = vec4f_scalar(&color_diff, dt * 2.0f);
		mapped[i] = vec4f_add(&mapped[i], &color_diff);
		++i;
	}
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}
