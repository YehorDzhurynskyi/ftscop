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

void    renderer_delete_gfx_mesh(t_mesh *mesh)
{
    glDeleteBuffers(1, &mesh->vbo_vertex);
    glDeleteBuffers(1, &mesh->vbo_color_tint);
    glDeleteBuffers(1, &mesh->ibo_faces);
    glDeleteVertexArrays(1, &mesh->vao);
}

void    renderer_delete_gfx_interactor(t_scene_interactor *interactor)
{
    glDeleteVertexArrays(1, &interactor->vao);
    glDeleteBuffers(1, &interactor->ibo_outline);
}
