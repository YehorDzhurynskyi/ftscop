/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_translate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "scene.h"

t_vec3f			transform_translate(const t_mat4f *orien, const t_vec3f *dpos)
{
	t_vec3f translate;
	t_vec3f i;
	t_vec3f j;
	t_vec3f k;

	calculate_basis_from_orientation(orien, &i, &j, &k);
	translate.x = dpos->x * i.x + dpos->y * j.x + dpos->z * k.x;
	translate.y = dpos->x * i.y + dpos->y * j.y + dpos->z * k.y;
	translate.z = dpos->x * i.z + dpos->y * j.z + dpos->z * k.z;
	return (translate);
}
