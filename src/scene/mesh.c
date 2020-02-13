/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

t_mesh  mesh_init(void)
{
    t_mesh  mesh;

    ft_memset(&mesh, 0x0, sizeof(t_mesh));
    return (mesh);
}

void    mesh_init_gfx(t_mesh *mesh)
{
    glGenVertexArrays(1, &mesh->vao);
    glBindVertexArray(mesh->vao);

    glGenBuffers(1, &mesh->ibo_faces);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo_faces);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->nfaces3 * 3 * sizeof(int), mesh->faces3, GL_STATIC_DRAW);

    glGenBuffers(1, &mesh->vbo_vertex);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo_vertex);
    glBufferData(GL_ARRAY_BUFFER, mesh->nvertices * sizeof(t_vec4f), mesh->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenBuffers(1, &mesh->vbo_color_tint);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo_color_tint);
    glBufferData(GL_ARRAY_BUFFER, mesh->nvertices * sizeof(t_vec4f), mesh->colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    FT_SAFE_FREE(mesh->faces3);
    FT_SAFE_FREE(mesh->vertices);
    FT_SAFE_FREE(mesh->colors);
}

void    mesh_delete(t_mesh *mesh)
{
    glDeleteBuffers(1, &mesh->vbo_vertex);
    glDeleteBuffers(1, &mesh->vbo_color_tint);
    glDeleteBuffers(1, &mesh->ibo_faces);
    glDeleteVertexArrays(1, &mesh->vao);
}
