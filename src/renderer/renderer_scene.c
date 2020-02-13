/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static void renderer_draw_actor(const t_actor *actor)
{
    t_gfx_program   *program;
    t_mat4f         model;

    program = &g_gfx_program_pool.phong;
    model = actor_calculate_matrix_model(actor);

    glUniformMatrix4fv(program->phong.u_location_model, 1, GL_FALSE, &model.data[0][0]);

    glBindVertexArray(actor->mesh->vao);

    glDrawElements(GL_TRIANGLES, actor->mesh->nfaces * 3, GL_UNSIGNED_INT, NULL);
}

void        renderer_draw_scene(const t_scene *scene)
{
    t_gfx_program   *program;
    t_mat4f         view;
    t_mat4f         proj;
    int             i;

    program = &g_gfx_program_pool.phong;
    glUseProgram(program->id);

    view = camera_calculate_matrix_view(&scene->camera);
    proj = camera_calculate_matrix_proj(&scene->camera);
    glUniformMatrix4fv(program->phong.u_location_view, 1, GL_FALSE, &view.data[0][0]);
    glUniformMatrix4fv(program->phong.u_location_proj, 1, GL_FALSE, &proj.data[0][0]);

    i = 0;
    while (i < scene->nactors)
    {
        renderer_draw_actor(&scene->actors[i++]);
    }
}
