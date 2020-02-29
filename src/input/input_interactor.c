/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_actor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "renderer/renderer.h"

t_bool  scene_interactor_init(t_scene_interactor *interactor, const t_scene *scene)
{
    t_bool result;

    interactor->scene_target = (t_scene*)scene;
    interactor->actor_selected = NULL;
    interactor->interaction_mode = TRANSLATION;
    if ((result = renderer_init_gfx_interactor(interactor)) == TRUE)
    {
        scene_interactor_select_actor(interactor, &scene->actor);
    }
    return (result);
}

void    scene_interactor_delete(t_scene_interactor *interactor)
{
    renderer_delete_gfx_interactor(interactor);
}

void    scene_interactor_select_actor(t_scene_interactor *interactor, const t_actor *actor)
{
    t_gfx_program   *program;

    program = &g_gfx_ctx.pool.noshading;
    glBindVertexArray(interactor->vao);

    glBindBuffer(GL_ARRAY_BUFFER, actor->mesh->vbo_vertex);
    glEnableVertexAttribArray(program->noshading.a_location_position);
    glVertexAttribPointer(program->noshading.a_location_position, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(program->noshading.a_location_color_tint, actor->mesh->nfaces * 6);

    glBindVertexArray(0);

    interactor->actor_selected = (t_actor*)actor;
}
