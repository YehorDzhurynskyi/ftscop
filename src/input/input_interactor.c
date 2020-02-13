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

t_scene_interactor  input_interactor_init(const t_scene *scene)
{
    t_scene_interactor  interactor;

    interactor.scene_target = scene;
    interactor.actor_selected = NULL;
    interactor.interaction_mode = TRANSLATION;
    return (interactor);
}

void    input_interactor_select_actor(t_scene_interactor *interactor, const t_actor *actor)
{
    int *mapped;
    int *indices;
    int i;

    indices = malloc(actor->mesh->nfaces * 6 * sizeof(int));
    assert(indices);
    // TODO: check null

    mapped = (int*)glMapNamedBuffer(actor->mesh->ibo_faces, GL_READ_ONLY);
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

    glUnmapNamedBuffer(actor->mesh->ibo_faces);

    glBindVertexArray(interactor->vao);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, actor->mesh->nfaces * 6 * sizeof(int), indices, GL_STATIC_DRAW);

    FT_SAFE_FREE(indices);

    interactor->actor_selected = actor;
}
