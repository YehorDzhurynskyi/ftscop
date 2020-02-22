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

typedef enum e_palette	t_palette;
enum e_palette
{
	CUSTOM,
	NATURE,
	FIRE
};

typedef struct s_material   t_material;
struct  s_material
{
	t_bool		wireframe;
	t_bool		smooth;
	t_bool		grayscale;
	t_palette	palette;
};

typedef struct s_mesh   t_mesh;
struct  s_mesh
{
    t_vec4f     *vertices;
    t_vec4f     *color_tints;
    int         nvertices;
    int         *faces;
    int         nfaces;

    t_vec3f     size;

    GLuint      vao;
    GLuint      vbo_vertex;
    GLuint      vbo_color_tint;
	GLuint      vbo_color;
    GLuint      ibo_faces;

    // TODO: add lines ibo for `l` param in .obj file
    // GLuint      ibo_lines;
};

t_mesh  mesh_init(void);
void    mesh_align(t_mesh *mesh);
void	mesh_colorize_bw(t_mesh *mesh);
void	mesh_colorize_rand(t_mesh *mesh);

#endif
