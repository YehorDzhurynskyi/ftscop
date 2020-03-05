/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "scene.h"
#include "renderer/renderer.h"

t_mat4f	actor_calculate_matrix_model(const t_actor *actor)
{
	t_mat4f scale;
	t_mat4f translation;
	t_mat4f sr;

	scale = calculate_matrix_scale(&actor->scale);
	translation = calculate_matrix_translation(&actor->position);
	sr = mat4f_mat4f_mult(&scale, &actor->orientation);
	return (mat4f_mat4f_mult(&sr, &translation));
}

t_vec3f	actor_radius_get(const t_actor *actor)
{
	return (vec3f_mult(&actor->mesh->size, &actor->scale));
}

float	actor_radius_max_get(const t_actor *actor)
{
	t_vec3f r;

	r = actor_radius_get(actor);
	return (FT_MAX(r.x, FT_MAX(r.y, r.z)));
}

void	actor_palette_set(t_actor *actor, const enum e_palette palette)
{
	actor->material.palette = palette;
	if (palette == Palette_RANDOM)
	{
		actor_colorize_random(actor);
	}
	else if (palette == Palette_NATURE)
	{
		actor_colorize_nature(actor);
	}
	else if (palette == Palette_FIRE)
	{
		actor_colorize_fire(actor);
	}
}
