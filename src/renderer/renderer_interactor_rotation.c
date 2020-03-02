/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_interactor_rotation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _USE_MATH_DEFINES // TODO: remove
#include <math.h>
#include "renderer.h"

void	renderer_draw_controls_rotation(const t_scene_interactor *interactor, const t_mat4f *vp)
{
	t_mat4f	mvp;
	t_vec3f	origin;
	t_vec3f	rxryrz[3];
	t_vec4f	colors[3];
	float	radius;

	origin = (t_vec3f){ 0.0f, 0.0f, 0.0f };
	colors[0] = (t_vec4f){ 0.0f, 0.0f, 1.0f, 1.0f };
	colors[1] = (t_vec4f){ 1.0f, 0.0f, 0.0f, 1.0f };
	colors[2] = (t_vec4f){ 0.0f, 1.0f, 0.0f, 1.0f };
	rxryrz[0] = (t_vec3f){ 0.0f, 0.0f, M_PI_2 };
	rxryrz[1] = (t_vec3f){ 0.0f, M_PI_2, 0.0f };
	rxryrz[2] = (t_vec3f){ -M_PI_2, 0.0f, 0.0f };
	radius = actor_radius_max_get(interactor->actor_selected);
	mvp = renderer_calculate_local_mvp(interactor->actor_selected, vp, &origin, &rxryrz[0]);
	renderer_draw_circle(&mvp, &colors[0], 40, 0.25f + radius);
	mvp = renderer_calculate_local_mvp(interactor->actor_selected, vp, &origin, &rxryrz[1]);
	renderer_draw_circle(&mvp, &colors[1], 40, 0.25f + radius);
	mvp = renderer_calculate_local_mvp(interactor->actor_selected, vp, &origin, &rxryrz[2]);
	renderer_draw_circle(&mvp, &colors[2], 40, 0.25f + radius);
}