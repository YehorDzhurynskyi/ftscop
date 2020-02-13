/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void    scene_delete(t_scene *scene)
{
    int i;

    i = 0;
    while (i < scene->nmeshes)
    {
        renderer_delete_gfx_mesh(&scene->meshes[i]);
    }

    FT_SAFE_FREE(scene->materials);
    FT_SAFE_FREE(scene->meshes);
    FT_SAFE_FREE(scene->actors);
}
