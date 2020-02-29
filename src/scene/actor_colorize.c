/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_colorize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void apply_grayscale(t_vec4f *color)
{
	float	gray;

	gray = (0.212f * color->x + 0.715f * color->y + 0.072f * color->z) / 3.0f;
	*color = (t_vec4f){ gray, gray, gray, 1.0f };
}

void	actor_colorize_random(t_actor* actor)
{
	int	i;

	i = 0;
	while (i < (int)actor->mesh->nvertices)
	{
		actor->material.color_target[i] = (t_vec4f) {
			rand() / (float)RAND_MAX,
			rand() / (float)RAND_MAX,
			rand() / (float)RAND_MAX,
			1.0f
		};
		if (actor->material.grayscale)
		{
			apply_grayscale(&actor->material.color_target[i]);
		}
		++i;
	}
}

void    actor_colorize_nature(t_actor* actor)
{
	int	i;

	i = 0;
	while (i < (int)actor->mesh->nvertices)
	{
		actor->material.color_target[i] = (t_vec4f) {
			actor->mesh->vertices[i].x * 0.4f + 0.4f,
			actor->mesh->vertices[i].y * 0.4f + 0.4f,
			actor->mesh->vertices[i].z * 0.4f + 0.4f,
			1.0f
		};
		if (actor->material.grayscale)
		{
			apply_grayscale(&actor->material.color_target[i]);
		}
		++i;
	}
}

void    actor_colorize_fire(t_actor* actor)
{
	int	i;

	i = 0;
	while (i < (int)actor->mesh->nvertices)
	{
		actor->material.color_target[i] = (t_vec4f) {
			actor->mesh->vertices[i].y * 0.4f + 0.4f,
			actor->mesh->vertices[i].z * 0.1f + actor->mesh->vertices[i].y * 0.4f + 0.1f,
			0.2f,
			1.0f
		};
		if (actor->material.grayscale)
		{
			apply_grayscale(&actor->material.color_target[i]);
		}
		++i;
	}
}
