/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_interactor.c                              :+:      :+:    :+:   */
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

static void renderer_draw_outlines(const t_scene_interactor *interactor)
{
    t_mat4f         model;
    t_gfx_program   *program;

    program = &g_gfx_program_pool.noshading;
    model = actor_calculate_matrix_model(interactor->actor_selected);

    glUniformMatrix4fv(program->noshading.u_location_model, 1, GL_FALSE, &model.data[0][0]);

    glBindVertexArray(interactor->vao);
    glVertexAttribDivisor(program->noshading.a_location_color_tint, interactor->actor_selected->mesh->nfaces * 6);

    const t_vec3f camera_pos = interactor->scene_target->camera.position;
    const t_vec3f actor_pos = interactor->actor_selected->position;
    const t_vec3f to_camera = vec3f_sub(&camera_pos, &actor_pos);
    glLineWidth(6.0f / vec3f_length(&to_camera));

    glDrawElements(GL_LINES, interactor->actor_selected->mesh->nfaces * 6, GL_UNSIGNED_INT, NULL);
}

static void renderer_draw_controls_translation(const t_scene_interactor *interactor)
{
    t_mat4f         model;
    t_gfx_program   *program;

    program = &g_gfx_program_pool.noshading;
    model = actor_calculate_matrix_model(interactor->actor_selected);
    glUniformMatrix4fv(program->noshading.u_location_model, 1, GL_FALSE, &model.data[0][0]);

    t_vec4f basis[] = {
        (t_vec4f) { 3.0f, 0.0f, 0.0f, 1.0f },
        (t_vec4f) { 0.0f, 3.0f, 0.0f, 1.0f },
        (t_vec4f) { 0.0f, 0.0f, 3.0f, 1.0f },
        (t_vec4f) { 0.0f, 0.0f, 0.0f, 1.0f }
    };
    int indices[6] = { 3, 0, 3, 1, 3, 2 };

    GLuint tempVAO;
    glGenVertexArrays(1, &tempVAO);
    glBindVertexArray(tempVAO);

    GLint ibo;
    glGenBuffers(1, &ibo);

    GLint vbos[2];
    glGenBuffers(2, vbos);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(t_vec4f), basis, GL_STATIC_DRAW);
    glVertexAttribPointer(program->noshading.a_location_position, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(program->noshading.a_location_position);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(t_vec4f), basis, GL_STATIC_DRAW);
    glVertexAttribPointer(program->noshading.a_location_color_tint, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(program->noshading.a_location_color_tint);

    glLineWidth(2.0f);
    glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, NULL);

    glDeleteBuffers(2, vbos);
    glDeleteBuffers(1, &ibo);
    glDeleteVertexArrays(1, &tempVAO);
}

static void renderer_draw_controls_rotation(const t_scene_interactor *interactor)
{
    t_gfx_program   *program;
    t_mat4f         view;
    t_mat4f         proj;
    t_mat4f         model;

    program = &g_gfx_program_pool.circle;
    glUseProgram(program->id);

    view = camera_calculate_matrix_view(&interactor->scene_target->camera);
    proj = camera_calculate_matrix_proj(&interactor->scene_target->camera);
    view = mat4f_mat4f_mult(&view, &proj);

    glUniform1i(program->circle.u_location_nsegments, 40);
    glUniform1f(program->circle.u_location_radius, 1.5f);

    GLuint tempVAO;
    glGenVertexArrays(1, &tempVAO);
    glBindVertexArray(tempVAO);

    glLineWidth(2.0f);

    model = actor_calculate_matrix_model(interactor->actor_selected);
    proj = mat4f_mat4f_mult(&model, &view);
    glUniformMatrix4fv(program->circle.u_location_mvp, 1, GL_FALSE, &proj.data[0][0]);
    glUniform4f(program->circle.u_location_color_tint, 0.0f, 0.0f, 1.0f, 1.0f);

    glDrawArrays(GL_POINTS, 0, 1);

    model = actor_calculate_matrix_model(interactor->actor_selected);
    t_vec3f drot1 = (t_vec3f) { M_PI / 2.0f, 0.0f, 0.0f };
    model = transform_rotate(&model, &drot1);
    proj = mat4f_mat4f_mult(&model, &view);
    glUniformMatrix4fv(program->circle.u_location_mvp, 1, GL_FALSE, &proj.data[0][0]);
    glUniform4f(program->circle.u_location_color_tint, 0.0f, 1.0f, 0.0f, 1.0f);

    glDrawArrays(GL_POINTS, 0, 1);

    model = actor_calculate_matrix_model(interactor->actor_selected);
    t_vec3f drot2 = (t_vec3f) { 0.0f, M_PI / 2.0f, 0.0f };
    model = transform_rotate(&model, &drot2);
    proj = mat4f_mat4f_mult(&model, &view);
    glUniformMatrix4fv(program->circle.u_location_mvp, 1, GL_FALSE, &proj.data[0][0]);
    glUniform4f(program->circle.u_location_color_tint, 1.0f, 0.0f, 0.0f, 1.0f);

    glDrawArrays(GL_POINTS, 0, 1);

    glDeleteVertexArrays(1, &tempVAO);
}

static void renderer_draw_controls_scaling(const t_scene_interactor *interactor)
{}

void        renderer_draw_interactor(const t_scene_interactor *interactor)
{
    t_mat4f         view;
    t_mat4f         proj;
    t_gfx_program   *program;

    if (interactor->actor_selected == NULL)
    {
        return;
    }

    program = &g_gfx_program_pool.noshading;

    glUseProgram(program->id);

    view = camera_calculate_matrix_view(&interactor->scene_target->camera);
    proj = camera_calculate_matrix_proj(&interactor->scene_target->camera);
    glUniformMatrix4fv(program->noshading.u_location_view, 1, GL_FALSE, &view.data[0][0]);
    glUniformMatrix4fv(program->noshading.u_location_proj, 1, GL_FALSE, &proj.data[0][0]);

    renderer_draw_outlines(interactor);
    if (interactor->interaction_mode == TRANSLATION)
    {
        renderer_draw_controls_translation(interactor);
    }
    else if (interactor->interaction_mode == ROTATION)
    {
        renderer_draw_controls_rotation(interactor);
    }
    else if (interactor->interaction_mode == SCALING)
    {
        renderer_draw_controls_scaling(interactor);
    }
}
