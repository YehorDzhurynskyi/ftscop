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

#define _USE_MATH_DEFINES // TODO: remove
#include <math.h>
#include "renderer.h"

static t_mat4f	get_mvp(const t_actor* actor,
                        const t_vec3f* basis,
                        const t_mat4f* vp,
                        const t_vec3f* rot,
                        const float offset)
{
    t_vec3f	local_position;

    local_position = vec3f_scalar(basis, offset);
    return (renderer_calculate_local_mvp(actor, vp, &local_position, rot));
}

void		    renderer_draw_controls_translation(
const t_scene_interactor* interactor, const t_mat4f* vp)
{
    t_mat4f	mvp;
    t_vec3f b[3];
    t_vec3f rt[3];
    t_vec4f colors[3];
    t_vec3f r;

    colors[0] = (t_vec4f){ 1.0f, 0.0f, 0.0f, 1.0f };
    colors[1] = (t_vec4f){ 0.0f, 1.0f, 0.0f, 1.0f };
    colors[2] = (t_vec4f){ 0.0f, 0.0f, 1.0f, 1.0f };
    rt[0] = (t_vec3f){ 0.0f, 0.0f, M_PI_2 };
    rt[1] = (t_vec3f){ 0.0f, M_PI_2, 0.0f };
    rt[2] = (t_vec3f){ -M_PI_2, 0.0f, 0.0f };
    r = actor_radius_get(interactor->actor_selected);
    renderer_draw_actor_basis(interactor->actor_selected, vp);
    calculate_basis_from_orientation(&interactor->actor_selected->orientation, &b[0], &b[1], &b[2]);
    mvp = get_mvp(interactor->actor_selected, &b[0], vp, &rt[0], 1.5f + r.x);
    renderer_draw_cone(&mvp, &colors[0], 8, 0.15f, 0.5f);
    mvp = get_mvp(interactor->actor_selected, &b[1], vp, &rt[1], 1.5f + r.y);
    renderer_draw_cone(&mvp, &colors[1], 8, 0.15f, 0.5f);
    mvp = get_mvp(interactor->actor_selected, &b[2], vp, &rt[2], 1.5f + r.z);
    renderer_draw_cone(&mvp, &colors[2], 8, 0.15f, 0.5f);
}
