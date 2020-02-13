/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# include "ft.h"
# include <glad/glad.h>

typedef struct s_material   t_material;
struct  s_material
{
    t_vec3f ambient;
    t_vec3f diffuse;
    t_vec3f transparency;
};

typedef struct s_mesh   t_mesh;
struct  s_mesh
{
    t_vec4f     *vertices;
    t_vec4f     *colors;
    int         nvertices;
    int         *faces;
    int         nfaces;

    GLuint      vao;
    GLuint      vbo_vertex;
    GLuint      vbo_color_tint;
    GLuint      ibo_faces;

    // TODO: add lines ibo for `l` param in .obj file
    // GLuint      ibo_lines;
};

t_mesh  mesh_init(void);

#endif
