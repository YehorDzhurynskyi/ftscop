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

enum	e_palette
{
	Palette_RANDOM,
	Palette_NATURE,
	Palette_FIRE,
	Palette_TEXTURE,

	Palette_COUNT
};

typedef struct s_material	t_material;
struct	s_material
{
	t_bool			wireframe;
	t_bool			smooth;
	t_bool			grayscale;
	enum e_palette	palette;
	GLuint			texture;
	t_vec4f			*color_target;
};

typedef struct s_mesh	t_mesh;
struct	s_mesh
{
	t_vec4f	*vertices;
	t_vec4f	*color_tints;
	int		nvertices;
	int		*faces;
	int		nfaces;

	t_vec3f	size;

	GLuint	vao;
	GLuint	vbo_vertex;
	GLuint	vbo_color_tint;
	GLuint	vbo_color;
	GLuint	ibo_faces;
	GLuint	ibo_wireframe;
};

t_bool	mesh_load_objfile(const char *filename, t_mesh *out_mesh);
void	mesh_delete(t_mesh *mesh);
void	mesh_align(t_mesh *mesh);

#endif
