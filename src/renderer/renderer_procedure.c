/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_procedure.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void	renderer_draw_circle(const t_mat4f *mvp, const t_vec4f *color, const unsigned int nsegments, const float radius)
{
	t_gfx_program	*program;

	program = &g_gfx_ctx.pool.circle;
	glUseProgram(program->id);
	glBindVertexArray(g_gfx_ctx.vao_null);
	glUniformMatrix4fv(program->circle.u_location_mvp, 1, GL_FALSE, &mvp->data[0][0]);
	glUniform4fv(program->circle.u_location_color_tint, 1, (GLfloat*)color);
	glUniform1i(program->circle.u_location_nsegments, nsegments);
	glUniform1f(program->circle.u_location_radius, radius);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
	glUseProgram(0);
}

void	renderer_draw_cone(const t_mat4f *mvp, const t_vec4f *color, const unsigned int nsegments, const float radius, const float height)
{
	t_gfx_program	*program;

	program = &g_gfx_ctx.pool.cone;
	glUseProgram(program->id);
	glBindVertexArray(g_gfx_ctx.vao_null);
	glUniformMatrix4fv(program->cone.u_location_mvp, 1, GL_FALSE, &mvp->data[0][0]);
	glUniform4fv(program->cone.u_location_color_tint, 1, (GLfloat*)color);
	glUniform1i(program->cone.u_location_nsegments, nsegments);
	glUniform1f(program->cone.u_location_height, height);
	glUniform1f(program->cone.u_location_radius, radius);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
	glUseProgram(0);
}

void	renderer_draw_cube(const t_mat4f *mvp, const t_vec4f *color, const float size)
{
	t_gfx_program	*program;

	program = &g_gfx_ctx.pool.cube;
	glUseProgram(program->id);
	glBindVertexArray(g_gfx_ctx.vao_null);
	glUniformMatrix4fv(program->cube.u_location_mvp, 1, GL_FALSE, &mvp->data[0][0]);
	glUniform4fv(program->cube.u_location_color_tint, 1, (GLfloat*)color);
	glUniform1f(program->cube.u_location_size, size);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
	glUseProgram(0);
}

void	renderer_draw_actor_basis(const t_actor *actor, const t_mat4f *vp)
{
	t_gfx_program	*program;
	t_mat4f			mvp;
	t_vec3f			origin;
	t_vec3f			radius;

	program = &g_gfx_ctx.pool.noshading;
	glUseProgram(program->id);
	GLuint tempvao;
	glGenVertexArrays(1, &tempvao);
	glBindVertexArray(tempvao);
	origin = (t_vec3f) { 0.0f, 0.0f, 0.0f };
	mvp = renderer_calculate_local_mvp(actor, vp, &origin, &origin);
	radius = actor_radius_get(actor);
	glUniformMatrix4fv(program->noshading.u_location_mvp, 1, GL_FALSE, &mvp.data[0][0]);
	t_vec4f basis[4];
	basis[0] = (t_vec4f) { 1.0f + radius.x, 0.0f, 0.0f, 1.0f };
	basis[1] = (t_vec4f) { 0.0f, 1.0f + radius.y, 0.0f, 1.0f };
	basis[2] = (t_vec4f) { 0.0f, 0.0f, 1.0f + radius.z, 1.0f };
	basis[3] = (t_vec4f) { 0.0f, 0.0f, 0.0f, 1.0f };
	int indices[6] = { 3, 0, 3, 1, 3, 2 };
	GLuint ibo;
	glGenBuffers(1, &ibo);
	GLuint vbos[2];
	glGenBuffers(2, vbos);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(t_vec4f), basis, GL_STATIC_DRAW);
	glVertexAttribPointer(program->noshading.a_location_position, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(program->noshading.a_location_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(t_vec4f), basis, GL_STATIC_DRAW);
	glVertexAttribPointer(program->noshading.a_location_color_tint, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(program->noshading.a_location_color_tint);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, NULL);
	glDeleteBuffers(2, vbos);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &tempvao);
	glBindVertexArray(0);
	glUseProgram(0);
}
