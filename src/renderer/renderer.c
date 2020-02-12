/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include <glad/glad.h>

void    renderer_draw_actor(const t_gctx *ctx, const t_actor *actor)
{
    t_mat4f model;
    GLint   model_location;

    model = actor_calculate_matrix_model(actor);
    model_location = glGetUniformLocation(ctx->program_id, "u_model");
    glBindVertexArray(actor->mesh->vao);
    glUniformMatrix4fv(model_location, 1, GL_FALSE, &model.data[0][0]);

    glDrawElements(GL_TRIANGLES, actor->mesh->nfaces3 * 3, GL_UNSIGNED_INT, NULL);
}

static void renderer_draw_controls_translation(const t_gctx *ctx, const t_actor *actor)
{
    t_mat4f model;
    GLint   model_location;

    model = actor_calculate_matrix_model(actor);
    model_location = glGetUniformLocation(ctx->program_id, "u_model");
}

static void renderer_draw_controls_rotation(const t_gctx *ctx, const t_actor *actor)
{
}

static void renderer_draw_controls_scaling(const t_gctx *ctx, const t_actor *actor)
{
}

void    renderer_draw_interactor(const t_gctx *ctx, const t_scene_interactor *interactor)
{
    if (interactor->actor_selected == NULL)
    {
        return;
    }
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
