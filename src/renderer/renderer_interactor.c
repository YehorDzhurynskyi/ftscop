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

static void renderer_draw_outlines(const t_gfx_ctx *ctx, const t_scene_interactor *interactor)
{
    t_mat4f         model;
    t_gfx_program   *program;

    program = &ctx->program_pool.noshading;
    model = actor_calculate_matrix_model(interactor->actor_selected);

    glUseProgram(program->id);

    glUniformMatrix4fv(program->noshading.u_location_view, 1, GL_FALSE, &ctx->view.data[0][0]);
    glUniformMatrix4fv(program->noshading.u_location_proj, 1, GL_FALSE, &ctx->proj.data[0][0]);
    glUniformMatrix4fv(program->noshading.u_location_model, 1, GL_FALSE, &model.data[0][0]);

    glBindVertexArray(interactor->vao);
    glVertexAttribDivisor(program->noshading.a_location_color_tint, interactor->actor_selected->mesh->nfaces * 6);

    glDrawElements(GL_LINES, interactor->actor_selected->mesh->nfaces * 6, GL_UNSIGNED_INT, NULL);
}

static void renderer_draw_controls_translation(const t_gfx_ctx *ctx, const t_actor *actor)
{
#if 0
    t_mat4f model;
    GLint   model_location;

    model = actor_calculate_matrix_model(actor);
    model_location = glGetUniformLocation(ctx->program_pool.phong.id, "u_model");
#endif
}

static void renderer_draw_controls_rotation(const t_gfx_ctx *ctx, const t_actor *actor)
{}

static void renderer_draw_controls_scaling(const t_gfx_ctx *ctx, const t_actor *actor)
{}

void        renderer_draw_interactor(const t_gfx_ctx *ctx, const t_scene_interactor *interactor)
{
    if (interactor->actor_selected == NULL)
    {
        return;
    }
    renderer_draw_outlines(ctx, interactor);
    if (interactor->interaction_mode == TRANSLATION)
    {
        renderer_draw_controls_translation(ctx, interactor->actor_selected);
    }
    else if (interactor->interaction_mode == ROTATION)
    {
        renderer_draw_controls_rotation(ctx, interactor->actor_selected);
    }
    else if (interactor->interaction_mode == SCALING)
    {
        renderer_draw_controls_scaling(ctx, interactor->actor_selected);
    }
}
