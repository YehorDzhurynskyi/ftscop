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
#include <SDL.h> // TODO: remove
#include <assert.h>
#include "renderer/renderer.h"

t_scene_interactor  input_interactor_init(const t_scene *scene)
{
    t_scene_interactor  interactor;

    interactor.scene_target = (t_scene*)scene;
    interactor.actor_selected = NULL;
    interactor.interaction_mode = TRANSLATION;
    return (interactor);
}

void    input_interactor_select_actor(t_scene_interactor *interactor, const t_actor *actor)
{
    t_gfx_program   *program;
    int             *mapped;
    int             *indices;
    int             i;

    indices = malloc(actor->mesh->nfaces * 6 * sizeof(int));
    assert(indices);
    // TODO: check null

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, actor->mesh->ibo_faces);
    mapped = (int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);
    assert(mapped);
    // TODO: check null

    i = 0;
    while (i < actor->mesh->nfaces)
    {
        indices[6 * i + 0] = mapped[3 * i + 0];
        indices[6 * i + 1] = mapped[3 * i + 1];
        indices[6 * i + 2] = mapped[3 * i + 0];
        indices[6 * i + 3] = mapped[3 * i + 2];
        indices[6 * i + 4] = mapped[3 * i + 1];
        indices[6 * i + 5] = mapped[3 * i + 2];
        ++i;
    }

    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

    program = &g_gfx_ctx.pool.noshading;
    glBindVertexArray(interactor->vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, interactor->ibo_outline);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, actor->mesh->nfaces * 6 * sizeof(int), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, actor->mesh->vbo_vertex);
    glEnableVertexAttribArray(program->noshading.a_location_position);
    glVertexAttribPointer(program->noshading.a_location_position, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(program->noshading.a_location_color_tint, actor->mesh->nfaces * 6);

    glBindVertexArray(0);

    FT_SAFE_FREE(indices);

    interactor->actor_selected = (t_actor*)actor;
}
