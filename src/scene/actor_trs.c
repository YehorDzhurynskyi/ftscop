/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_trs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <math.h>

void	calculate_basis_from_orientation(const t_mat4f *orien,
										t_vec3f *i,
										t_vec3f *j,
										t_vec3f *k)
{
	*i = (t_vec3f) { orien->s0, orien->s1, orien->s2 };
	*j = (t_vec3f) { orien->s4, orien->s5, orien->s6 };
	*k = (t_vec3f) { orien->s8, orien->s9, orien->sa };
}

t_mat4f	calculate_matrix_scale(const t_vec3f *scl)
{
	t_mat4f scale;

	scale = mat4f_identity();
	scale.data[0][0] = scl->x;
	scale.data[1][1] = scl->y;
	scale.data[2][2] = scl->z;
	scale.data[3][3] = 1.0f;
	return (scale);
}

t_mat4f	calculate_matrix_orientation_from_basis(const t_vec3f *i,
												const t_vec3f *j,
												const t_vec3f *k)
{
	t_mat4f	mat;

	mat = mat4f_identity();
	mat.data[0][0] = i->x;
	mat.data[0][1] = i->y;
	mat.data[0][2] = i->z;
	mat.data[1][0] = j->x;
	mat.data[1][1] = j->y;
	mat.data[1][2] = j->z;
	mat.data[2][0] = k->x;
	mat.data[2][1] = k->y;
	mat.data[2][2] = k->z;
	return (mat);
}

t_mat4f	calculate_matrix_translation(const t_vec3f *pos)
{
	t_mat4f translation;

	translation = mat4f_identity();
	translation.data[3][0] = pos->x;
	translation.data[3][1] = pos->y;
	translation.data[3][2] = pos->z;
	return (translation);
}
