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

#include "renderer.h"

static void renderer_draw_outlines(const t_scene_interactor *interactor)
{
    t_mat4f         model;
    t_mat4f         view;
    t_mat4f         proj;
    t_gfx_program   *program;

    program = &g_gfx_program_pool.noshading;
    model = actor_calculate_matrix_model(interactor->actor_selected);

    glUseProgram(program->id);

    view = camera_calculate_matrix_view(&interactor->scene_target->camera);
    proj = camera_calculate_matrix_proj(&interactor->scene_target->camera);

    glUniformMatrix4fv(program->noshading.u_location_view, 1, GL_FALSE, &view.data[0][0]);
    glUniformMatrix4fv(program->noshading.u_location_proj, 1, GL_FALSE, &proj.data[0][0]);
    glUniformMatrix4fv(program->noshading.u_location_model, 1, GL_FALSE, &model.data[0][0]);

    glBindVertexArray(interactor->vao);
    glVertexAttribDivisor(program->noshading.a_location_color_tint, interactor->actor_selected->mesh->nfaces * 6);

    const t_vec3f camera_pos = interactor->scene_target->camera.position;
    const t_vec3f actor_pos = interactor->actor_selected->position;
    const t_vec3f to_camera = vec3f_sub(&camera_pos, &actor_pos);
    glLineWidth(6.0f / vec3f_length(&to_camera));

    glDrawElements(GL_LINES, interactor->actor_selected->mesh->nfaces * 6, GL_UNSIGNED_INT, NULL);
}

static void renderer_draw_controls_translation(const t_actor *actor)
{
#if 0
    t_mat4f model;
    GLint   model_location;

    model = actor_calculate_matrix_model(actor);
    model_location = glGetUniformLocation(ctx->program_pool.phong.id, "u_model");
#endif
}

static void renderer_draw_controls_rotation(const t_actor *actor)
{}

static void renderer_draw_controls_scaling(const t_actor *actor)
{}

void        renderer_draw_interactor(const t_scene_interactor *interactor)
{
    if (interactor->actor_selected == NULL)
    {
        return;
    }
    renderer_draw_outlines(interactor);
    if (interactor->interaction_mode == TRANSLATION)
    {
        renderer_draw_controls_translation(interactor->actor_selected);
    }
    else if (interactor->interaction_mode == ROTATION)
    {
        renderer_draw_controls_rotation(interactor->actor_selected);
    }
    else if (interactor->interaction_mode == SCALING)
    {
        renderer_draw_controls_scaling(interactor->actor_selected);
    }
}
