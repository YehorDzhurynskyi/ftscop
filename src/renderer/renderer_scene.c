/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "renderer.h"

static void	renderer_draw_grid(const t_mat4f *vp)
{
	t_gfx_program_grid	*program;
	t_mat4f				model;
	t_mat4f				mvp;

	program = &g_gfx_ctx.pool.grid;
	glUseProgram(program->id);
	glBindVertexArray(g_gfx_ctx.vao_null);
	model = mat4f_identity();
	model = transform_rotate_x(&model, M_PI_2);
	mvp = mat4f_mat4f_mult(&model, vp);
	glUniformMatrix4fv(program->u_location_mvp, 1, GL_FALSE, &mvp.data[0][0]);
	glUniform1f(program->u_location_dimension, 50.0f);
	glUniform1i(program->u_location_nsteps, 50);
	glUniform4f(program->u_location_color_tint, 0.55f, 0.55f, 0.55f, 1.0f);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
	glUseProgram(0);
}

static void	renderer_draw_actor(const t_actor *actor, const t_mat4f *vp)
{
	t_gfx_program_phong	*program;
	t_mat4f				model;

	program = &g_gfx_ctx.pool.phong;
	glUseProgram(program->id);
	glBindVertexArray(actor->mesh->vao);
	model = actor_calculate_matrix_model(actor);
	model = mat4f_mat4f_mult(&model, vp);
	glUniformMatrix4fv(program->u_location_mvp, 1, GL_FALSE, &model.data[0][0]);
	glUniform1i(program->u_location_palette, actor->material.palette);
	glUniform1i(program->u_location_is_smooth_mode_enabled,
	actor->material.smooth);
	glBindTexture(GL_TEXTURE_2D, actor->material.texture);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, actor->material.wireframe ?
	actor->mesh->ibo_wireframe : actor->mesh->ibo_faces);
	if (actor->material.wireframe)
		glDrawElements(GL_LINES, actor->mesh->nfaces * 6,
		GL_UNSIGNED_INT, NULL);
	else
		glDrawElements(GL_TRIANGLES, actor->mesh->nfaces * 3,
		GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
	glUseProgram(0);
}

void		renderer_draw_scene(const t_scene *scene)
{
	t_mat4f view;
	t_mat4f proj;

	view = camera_calculate_matrix_view(&scene->camera);
	proj = camera_calculate_matrix_proj(&scene->camera);
	view = mat4f_mat4f_mult(&view, &proj);
	renderer_draw_grid(&view);
	renderer_draw_actor(&scene->actor, &view);
}
