/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static t_bool   init_phong_program(t_gfx_program *program)
{
    program->id = shader_load("shaders/phong.vert", "shaders/phong.frag");
    if (!program->id)
    {
        return (FALSE);
    }

    program->phong.u_location_model = glGetUniformLocation(program->id, "u_model");
    program->phong.u_location_view = glGetUniformLocation(program->id, "u_view");
    program->phong.u_location_proj = glGetUniformLocation(program->id, "u_projection");
    program->phong.a_location_position = glGetAttribLocation(program->id, "a_position");
    program->phong.a_location_color_tint = glGetAttribLocation(program->id, "a_color_tint");
    if (program->phong.a_location_position < 0 ||
        program->phong.a_location_color_tint < 0 ||
        program->phong.u_location_model < 0 ||
        program->phong.u_location_view < 0 ||
        program->phong.u_location_proj < 0)
    {
        glDeleteProgram(program->id);
        return (FALSE);
    }

    return (TRUE);
}

t_bool          renderer_init(t_gfx_ctx *ctx)
{
    if (!init_phong_program(&ctx->program_pool.phong))
    {
        // TODO: release all resources
        return (FALSE);
    }
    return (TRUE);
}

void            renderer_delete(t_gfx_ctx *ctx)
{
    glDeleteProgram(ctx->program_pool.phong.id);
}
