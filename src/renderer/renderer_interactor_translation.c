/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_interactor_translation.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "renderer.h"

static t_mat4f	get_mvp(const t_actor *actor,
						const t_vec3f *basis,
						const t_mat4f *vp,
						const t_vec4f *crunch)
{
	t_vec3f	local_position;
	t_vec3f	rot;

	rot = (t_vec3f) { crunch->x, crunch->y, crunch->z };
	local_position = vec3f_scalar(basis, crunch->w);
	return (renderer_calculate_local_mvp(actor, vp, &local_position, &rot));
}

void			renderer_draw_controls_translation(
const t_scene_interactor *interactor, const t_mat4f *vp)
{
	t_mat4f	mvp;
	t_vec3f b[3];
	t_vec4f rt[3];
	t_vec4f colors[3];
	t_vec3f r;

	r = actor_radius_get(interactor->actor_selected);
	colors[0] = (t_vec4f){ 1.0f, 0.0f, 0.0f, 1.0f };
	colors[1] = (t_vec4f){ 0.0f, 1.0f, 0.0f, 1.0f };
	colors[2] = (t_vec4f){ 0.0f, 0.0f, 1.0f, 1.0f };
	rt[0] = (t_vec4f){ 0.0f, 0.0f, M_PI_2, 1.5f + r.x };
	rt[1] = (t_vec4f){ 0.0f, M_PI_2, 0.0f, 1.5f + r.y };
	rt[2] = (t_vec4f){ -M_PI_2, 0.0f, 0.0f, 1.5f + r.z };
	renderer_draw_actor_basis(interactor->actor_selected, vp);
	calculate_basis_from_orientation(&interactor->actor_selected->orientation,
	&b[0], &b[1], &b[2]);
	mvp = get_mvp(interactor->actor_selected, &b[0], vp, &rt[0]);
	renderer_draw_cone(&mvp, &colors[0], 0.15f, 0.5f);
	mvp = get_mvp(interactor->actor_selected, &b[1], vp, &rt[1]);
	renderer_draw_cone(&mvp, &colors[1], 0.15f, 0.5f);
	mvp = get_mvp(interactor->actor_selected, &b[2], vp, &rt[2]);
	renderer_draw_cone(&mvp, &colors[2], 0.15f, 0.5f);
}
