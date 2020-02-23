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
#include <math.h>
#include <assert.h>

t_mesh  mesh_init(void)
{
    t_mesh  mesh;

    ft_memset(&mesh, 0x0, sizeof(t_mesh));
    return (mesh);
}

static t_vec4f determine_origin(const t_mesh *mesh)
{
    t_vec3f max;
    t_vec3f min;
    t_vec3f origin;
    int     i;

    min = (t_vec3f){ FLT_MAX, FLT_MAX, FLT_MAX };
    max = (t_vec3f){ -FLT_MAX, -FLT_MAX, -FLT_MAX };
    i = 0;
    while (i < mesh->nvertices)
    {
        min.x = FT_MIN(min.x, mesh->vertices[i].x);
        min.y = FT_MIN(min.y, mesh->vertices[i].y);
        min.z = FT_MIN(min.z, mesh->vertices[i].z);
        max.x = FT_MAX(max.x, mesh->vertices[i].x);
        max.y = FT_MAX(max.y, mesh->vertices[i].y);
        max.z = FT_MAX(max.z, mesh->vertices[i].z);
        ++i;
    }
    origin = vec3f_sub(&max, &min);
    origin = vec3f_scalar(&origin, 0.5f);
    origin = vec3f_add(&origin, &min);
    return ((t_vec4f) { origin.x, origin.y, origin.z, 0.0f });
}

void    mesh_align(t_mesh *mesh)
{
    t_vec4f origin;
    int     i;

    mesh->size = (t_vec3f) { -FLT_MAX, -FLT_MAX, -FLT_MAX };
    origin = determine_origin(mesh);
    i = 0;
    while (i < mesh->nvertices)
    {
        mesh->vertices[i] = vec4f_sub(&mesh->vertices[i], &origin);
        mesh->size.x = FT_MAX(mesh->size.x, fabsf(mesh->vertices[i].x));
        mesh->size.y = FT_MAX(mesh->size.y, fabsf(mesh->vertices[i].y));
        mesh->size.z = FT_MAX(mesh->size.z, fabsf(mesh->vertices[i].z));
        ++i;
    }
}

void	mesh_colorize_rand(t_mesh *mesh)
{
	unsigned int	i;
	t_vec4f			*mapped;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vbo_color);
    mapped = (t_vec4f*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
    assert(mapped);
    // TODO: check null

	i = 0;
	while (i < mesh->nvertices)
	{
		mapped[i++] = (t_vec4f) { rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1.0f };
    }

    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}
