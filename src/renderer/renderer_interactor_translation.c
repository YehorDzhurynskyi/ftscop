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

void    renderer_draw_controls_translation(const t_scene_interactor *interactor, const t_mat4f* vp)
{
    t_mat4f mvp;
    t_vec3f ijk[3];
    t_vec3f rxryrz[3];
    t_vec4f colors[3];

    colors[0] = (t_vec4f){ 1.0f, 0.0f, 0.0f, 1.0f };
    colors[1] = (t_vec4f){ 0.0f, 1.0f, 0.0f, 1.0f };
    colors[2] = (t_vec4f){ 0.0f, 0.0f, 1.0f, 1.0f };
    rxryrz[0] = (t_vec3f){ 0.0f, 0.0f, M_PI_2 };
    rxryrz[1] = (t_vec3f){ 0.0f, M_PI_2, 0.0f };
    rxryrz[2] = (t_vec3f){ -M_PI_2, 0.0f, 0.0f };
    const float height = 0.5f;
    renderer_draw_actor_basis(interactor->actor_selected, vp);
    calculate_basis_from_orientation(&interactor->actor_selected->orientation, &ijk[0], &ijk[1], &ijk[2]);

    ijk[0] = vec3f_scalar(&ijk[0], 3.0f + height);
    mvp = renderer_calculate_local_mvp(interactor->actor_selected, vp, &ijk[0], &rxryrz[0]);
    renderer_draw_cone(&mvp, &colors[0], 8, 0.15f, height);

    ijk[1] = vec3f_scalar(&ijk[1], 3.0f + height);
    mvp = renderer_calculate_local_mvp(interactor->actor_selected, vp, &ijk[1], &rxryrz[1]);
    renderer_draw_cone(&mvp, &colors[1], 8, 0.15f, height);

    ijk[2] = vec3f_scalar(&ijk[2], 3.0f + height);
    mvp = renderer_calculate_local_mvp(interactor->actor_selected, vp, &ijk[2], &rxryrz[2]);
    renderer_draw_cone(&mvp, &colors[2], 8, 0.15f, height);
}
