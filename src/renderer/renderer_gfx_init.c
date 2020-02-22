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

static t_bool	renderer_init_gfx_mesh_wireframe_element_buffer(t_mesh *mesh)
{
    int             *mapped;
    int             *indices;
    int             i;

    indices = malloc(mesh->nfaces * 6 * sizeof(int));
	if (!indices)
	{
		return (FALSE);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo_faces);
    mapped = (int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);
	if (!mapped)
	{
		return (FALSE);
	}

    i = 0;
    while (i < mesh->nfaces)
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
    glBindVertexArray(mesh->vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo_wireframe);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->nfaces * 6 * sizeof(int), indices, GL_STATIC_DRAW);

    FT_SAFE_FREE(indices);
	return (TRUE);
}

t_bool  renderer_init_gfx_mesh(t_mesh *mesh)
{
    t_gfx_program   *program;

    program = &g_gfx_ctx.pool.phong;

    glGenVertexArrays(1, &mesh->vao);
    glGenBuffers(1, &mesh->ibo_faces);
	glGenBuffers(1, &mesh->ibo_wireframe);
    glGenBuffers(1, &mesh->vbo_vertex);
    glGenBuffers(1, &mesh->vbo_color_tint);
	glGenBuffers(1, &mesh->vbo_color);

    if (!mesh->vao || !mesh->ibo_faces || !mesh->ibo_wireframe ||
    !mesh->vbo_vertex || !mesh->vbo_color_tint)
    {
        renderer_delete_gfx_mesh(mesh);
        return (FALSE);
    }

    glBindVertexArray(mesh->vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo_faces);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->nfaces * 3 * sizeof(int), mesh->faces, GL_STATIC_DRAW);

	renderer_init_gfx_mesh_wireframe_element_buffer(mesh);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo_vertex);
    glBufferData(GL_ARRAY_BUFFER, mesh->nvertices * sizeof(t_vec4f), mesh->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(program->phong.a_location_position);
    glVertexAttribPointer(program->phong.a_location_position, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo_color_tint);
    glBufferData(GL_ARRAY_BUFFER, mesh->nvertices * sizeof(t_vec4f), mesh->color_tints, GL_STATIC_DRAW);
    glEnableVertexAttribArray(program->phong.a_location_color_tint);
    glVertexAttribPointer(program->phong.a_location_color_tint, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo_color);
    glBufferData(GL_ARRAY_BUFFER, mesh->nvertices * sizeof(t_vec4f), NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(program->phong.a_location_color);
    glVertexAttribPointer(program->phong.a_location_color, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);

    return (TRUE);
}

t_bool  renderer_init_gfx_interactor(t_scene_interactor *interactor)
{
    t_gfx_program   *program;

    program = &g_gfx_ctx.pool.noshading;

    glGenVertexArrays(1, &interactor->vao);
    glGenBuffers(1, &interactor->vbo_outline_color);

    if (!interactor->vao || !interactor->vbo_outline_color)
    {
        renderer_delete_gfx_interactor(interactor);
        return (FALSE);
    }

    glBindVertexArray(interactor->vao);

    glBindBuffer(GL_ARRAY_BUFFER, interactor->vbo_outline_color);
    const t_vec4f color = (t_vec4f) { 0.05f, 0.05f, 0.05f, 1.0f };
    glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec4f), &color, GL_STATIC_DRAW);
    glEnableVertexAttribArray(program->noshading.a_location_color_tint);
    glVertexAttribPointer(program->noshading.a_location_color_tint, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(program->noshading.a_location_color_tint, 0);

    glBindVertexArray(0);

    return (TRUE);
}
