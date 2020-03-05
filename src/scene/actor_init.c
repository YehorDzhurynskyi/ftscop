/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "renderer/renderer.h"
#include <math.h>

void	actor_init(t_actor *actor, t_mesh *mesh, const t_texture *texture)
{
	actor->mesh = mesh;
	actor->position = (t_vec3f){ 0.0f, 0.0f, 0.0f };
	actor->orientation = mat4f_identity();
	actor->scale = (t_vec3f){ 1.0f, 1.0f, 1.0f };
	actor->material.smooth = TRUE;
	actor->material.wireframe = FALSE;
	actor->material.grayscale = FALSE;
	actor->material.color_target = malloc(sizeof(t_vec4f) * mesh->nvertices);
	actor_palette_set(actor, Palette_RANDOM);
	glGenTextures(1, &actor->material.texture);
	glBindTexture(GL_TEXTURE_2D, actor->material.texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height,
	0, GL_BGR, GL_UNSIGNED_BYTE, texture->raw);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void	actor_delete(t_actor *actor)
{
	FT_SAFE_FREE(actor->material.color_target);
	glDeleteTextures(1, &actor->material.texture);
}
