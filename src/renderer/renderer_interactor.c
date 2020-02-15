/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_interactor.c                              :+:      :+:    :+:   */
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

static void renderer_draw_outlines(const t_scene_interactor *interactor, const t_mat4f *vp)
{
    t_gfx_program   *program;
    t_mat4f         model;

    program = &g_gfx_ctx.pool.noshading;
    glUseProgram(program->id);
    glBindVertexArray(interactor->vao);

    model = actor_calculate_matrix_model(interactor->actor_selected);
    model = mat4f_mat4f_mult(&model, vp);
    glUniformMatrix4fv(program->noshading.u_location_mvp, 1, GL_FALSE, &model.data[0][0]);

    const t_vec3f camera_pos = interactor->scene_target->camera.position;
    const t_vec3f actor_pos = interactor->actor_selected->position;
    const t_vec3f to_camera = vec3f_sub(&camera_pos, &actor_pos);
    glLineWidth(6.0f / vec3f_length(&to_camera));

    glDrawElements(GL_LINES, interactor->actor_selected->mesh->nfaces * 6, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
    glUseProgram(0);
}

static void renderer_draw_controls_translation(const t_scene_interactor *interactor, const t_mat4f* vp)
{
    t_actor actor;
    t_mat4f model;
    t_vec3f i;
    t_vec3f j;
    t_vec3f k;
    t_vec4f colors[3];

    colors[0] = (t_vec4f){ 0.0f, 0.0f, 1.0f, 1.0f };
    colors[1] = (t_vec4f){ 0.0f, 1.0f, 0.0f, 1.0f };
    colors[2] = (t_vec4f){ 1.0f, 0.0f, 0.0f, 1.0f };
    const float height = 0.5f;
    renderer_draw_actor_basis(interactor->actor_selected, vp);
    calculate_basis_from_orientation(&interactor->actor_selected->orientation, &i, &j, &k);

    ft_memcpy(&actor, interactor->actor_selected, sizeof(t_actor));
    j = vec3f_scalar(&j, 3.0f + height);
    actor.position = vec3f_add(&actor.position, &j);
    model = actor_calculate_matrix_model(&actor);
    model = mat4f_mat4f_mult(&model, vp);
    renderer_draw_cone(&model, &colors[1], 8, 0.15f, height);

    ft_memcpy(&actor, interactor->actor_selected, sizeof(t_actor));
    i = vec3f_scalar(&i, 3.0f + height);
    actor.orientation = transform_rotate_z(&actor.orientation, M_PI_2);
    actor.position = vec3f_add(&actor.position, &i);
    model = actor_calculate_matrix_model(&actor);
    model = mat4f_mat4f_mult(&model, vp);
    renderer_draw_cone(&model, &colors[2], 8, 0.15f, height);

    ft_memcpy(&actor, interactor->actor_selected, sizeof(t_actor));
    k = vec3f_scalar(&k, 3.0f + height);
    actor.orientation = transform_rotate_x(&actor.orientation, -M_PI_2);
    actor.position = vec3f_add(&actor.position, &k);
    model = actor_calculate_matrix_model(&actor);
    model = mat4f_mat4f_mult(&model, vp);
    renderer_draw_cone(&model, &colors[0], 8, 0.15f, height);
}

static void renderer_draw_controls_rotation(const t_scene_interactor *interactor, const t_mat4f* vp)
{
    t_actor actor;
    t_mat4f model;
    t_vec4f colors[3];

    colors[0] = (t_vec4f) { 0.0f, 0.0f, 1.0f, 1.0f };
    colors[1] = (t_vec4f) { 0.0f, 1.0f, 0.0f, 1.0f };
    colors[2] = (t_vec4f) { 1.0f, 0.0f, 0.0f, 1.0f };
    model = actor_calculate_matrix_model(interactor->actor_selected);
    model = mat4f_mat4f_mult(&model, vp);
    renderer_draw_circle(&model, &colors[0], 40, 1.5f);

    ft_memcpy(&actor, interactor->actor_selected, sizeof(t_actor));
    actor.orientation = transform_rotate_x(&actor.orientation, M_PI_2);
    model = actor_calculate_matrix_model(&actor);
    model = mat4f_mat4f_mult(&model, vp);
    renderer_draw_circle(&model, &colors[1], 40, 1.5f);

    ft_memcpy(&actor, interactor->actor_selected, sizeof(t_actor));
    actor.orientation = transform_rotate_y(&actor.orientation, M_PI_2);
    model = actor_calculate_matrix_model(&actor);
    model = mat4f_mat4f_mult(&model, vp);
    renderer_draw_circle(&model, &colors[2], 40, 1.5f);
}

static void renderer_draw_controls_scaling(const t_scene_interactor *interactor)
{}

void        renderer_draw_interactor(const t_scene_interactor *interactor)
{
    t_mat4f view;
    t_mat4f proj;

    if (interactor->actor_selected == NULL)
    {
        return;
    }

    view = camera_calculate_matrix_view(&interactor->scene_target->camera);
    proj = camera_calculate_matrix_proj(&interactor->scene_target->camera);
    view = mat4f_mat4f_mult(&view, &proj);
    renderer_draw_outlines(interactor, &view);
    if (interactor->interaction_mode == TRANSLATION)
    {
        renderer_draw_controls_translation(interactor, &view);
    }
    else if (interactor->interaction_mode == ROTATION)
    {
        renderer_draw_controls_rotation(interactor, &view);
    }
    else if (interactor->interaction_mode == SCALING)
    {
        // renderer_draw_controls_scaling(interactor);
    }
}
