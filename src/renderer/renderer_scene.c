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

static void renderer_draw_actor(const t_gfx_ctx *ctx, const t_actor *actor)
{
    t_mat4f         model;
    t_gfx_program   *program;

    program = &ctx->program_pool.phong;
    model = actor_calculate_matrix_model(actor);

    glUseProgram(program->id);

    glUniformMatrix4fv(program->phong.u_location_view, 1, GL_FALSE, &ctx->view.data[0][0]);
    glUniformMatrix4fv(program->phong.u_location_proj, 1, GL_FALSE, &ctx->proj.data[0][0]);
    glUniformMatrix4fv(program->phong.u_location_model, 1, GL_FALSE, &model.data[0][0]);

    glBindVertexArray(actor->mesh->vao);

    glDrawElements(GL_TRIANGLES, actor->mesh->nfaces3 * 3, GL_UNSIGNED_INT, NULL);
}

void        renderer_draw_scene(const t_gfx_ctx *ctx, const t_scene *scene)
{
    int i;

    i = 0;
    while (i < scene->nactors)
    {
        renderer_draw_actor(ctx, &scene->actors[i++]);
    }
}
