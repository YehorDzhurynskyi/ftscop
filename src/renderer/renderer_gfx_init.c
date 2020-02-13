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

t_bool  renderer_init_gfx_mesh(t_mesh *mesh)
{
    t_gfx_program   *program;

    program = &g_gfx_program_pool.phong;

    glGenVertexArrays(1, &mesh->vao);
    glGenBuffers(1, &mesh->ibo_faces);
    glGenBuffers(1, &mesh->vbo_vertex);
    glGenBuffers(1, &mesh->vbo_color_tint);

    if (!mesh->vao || !mesh->ibo_faces ||
    !mesh->vbo_vertex || !mesh->vbo_color_tint)
    {
        renderer_delete_gfx_mesh(mesh);
        return (FALSE);
    }

    glBindVertexArray(mesh->vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo_faces);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->nfaces * 3 * sizeof(int), mesh->faces, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo_vertex);
    glBufferData(GL_ARRAY_BUFFER, mesh->nvertices * sizeof(t_vec4f), mesh->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(program->phong.a_location_position);
    glVertexAttribPointer(program->phong.a_location_position, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo_color_tint);
    glBufferData(GL_ARRAY_BUFFER, mesh->nvertices * sizeof(t_vec4f), mesh->colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(program->phong.a_location_color_tint);
    glVertexAttribPointer(program->phong.a_location_color_tint, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    return (TRUE);
}

t_bool  renderer_init_gfx_interactor(t_scene_interactor *interactor)
{
    t_gfx_program   *program;

    program = &g_gfx_program_pool.noshading;

    glGenVertexArrays(1, &interactor->vao);
    glGenBuffers(1, &interactor->ibo_outline);
    glGenBuffers(1, &interactor->vbo_outline_color);

    if (!interactor->vao || !interactor->ibo_outline)
    {
        renderer_delete_gfx_interactor(interactor);
        return (FALSE);
    }

    glBindVertexArray(interactor->vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, interactor->ibo_outline);
    glBindBuffer(GL_ARRAY_BUFFER, interactor->vbo_outline_color);
    const t_vec4f color = (t_vec4f) { 1.0f, 0.0f, 1.0f, 1.0f };
    glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec4f), &color, GL_STATIC_DRAW);
    glEnableVertexAttribArray(program->noshading.a_location_color_tint);
    glVertexAttribPointer(program->noshading.a_location_color_tint, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(program->noshading.a_location_color_tint, 0);

    return (TRUE);
}
