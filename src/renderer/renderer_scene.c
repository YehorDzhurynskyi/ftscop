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

#define _USE_MATH_DEFINES // TODO: remove
#include <math.h>
#include "renderer.h"

static void renderer_draw_grid(const t_mat4f *view, const t_mat4f *proj)
{
    t_gfx_program   *program;
    t_mat4f         model;
    t_mat4f         mvp;

    program = &g_gfx_program_pool.grid;
    glUseProgram(program->id);

    mvp = mat4f_mat4f_mult(view, proj);
    t_vec3f drot = (t_vec3f) { M_PI / 2.0f, 0.0f, 0.0f };

    model = mat4f_identity();
    model = transform_rotate(&model, &drot);
    mvp = mat4f_mat4f_mult(&model, &mvp);
    glUniformMatrix4fv(program->grid.u_location_mvp, 1, GL_FALSE, &mvp.data[0][0]);
    glUniform1f(program->grid.u_location_dimension, 50.0f);
    glUniform1i(program->grid.u_location_nsteps, 50);
    glUniform4f(program->grid.u_location_color_tint, 0.55f, 0.55f, 0.55f, 1.0f);

    GLuint tempVAO;
    glGenVertexArrays(1, &tempVAO);
    glBindVertexArray(tempVAO);

    glLineWidth(0.15f);
    glDrawArrays(GL_POINTS, 0, 1);

    glDeleteVertexArrays(1, &tempVAO);
}

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

    view = camera_calculate_matrix_view(&scene->camera);
    proj = camera_calculate_matrix_proj(&scene->camera);
    renderer_draw_grid(&view, &proj);

    program = &g_gfx_program_pool.phong;
    glUseProgram(program->id);
    glUniformMatrix4fv(program->phong.u_location_view, 1, GL_FALSE, &view.data[0][0]);
    glUniformMatrix4fv(program->phong.u_location_proj, 1, GL_FALSE, &proj.data[0][0]);

    i = 0;
    while (i < scene->nactors)
    {
        renderer_draw_actor(&scene->actors[i++]);
    }
}
