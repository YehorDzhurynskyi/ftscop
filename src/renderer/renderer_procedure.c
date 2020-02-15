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

void    renderer_draw_circle(const t_mat4f *mvp, const t_vec4f *color, const unsigned int nsegments, const float radius)
{
    t_gfx_program *program;

    program = &g_gfx_ctx.pool.circle;
    glUseProgram(program->id);
    glBindVertexArray(g_gfx_ctx.vao_null);

    glUniformMatrix4fv(program->circle.u_location_mvp, 1, GL_FALSE, &mvp->data[0][0]);
    glUniform4fv(program->circle.u_location_color_tint, 1, color);
    glUniform1i(program->circle.u_location_nsegments, nsegments);
    glUniform1f(program->circle.u_location_radius, radius);

    glLineWidth(2.0f);
    glDrawArrays(GL_POINTS, 0, 1);

    glBindVertexArray(0);
    glUseProgram(0);
}
