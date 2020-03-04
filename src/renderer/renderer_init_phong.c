/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_init_phong_program.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

t_bool   renderer_init_phong_program(t_gfx_program* program)
{
    program->id = shader_load("shaders/phong.vert", "shaders/phong.frag", NULL);
    if (!program->id)
    {
        return (FALSE);
    }
    program->phong.u_location_mvp = glGetUniformLocation(program->id, "u_mvp");
    program->phong.u_location_is_smooth_mode_enabled = glGetUniformLocation(program->id, "u_is_smooth_mode_enabled");
    program->phong.u_location_texture = glGetUniformLocation(program->id, "u_texture");
    program->phong.u_location_palette = glGetUniformLocation(program->id, "u_palette");
    program->phong.a_location_position = glGetAttribLocation(program->id, "a_position");
    program->phong.a_location_color_tint = glGetAttribLocation(program->id, "a_color_tint");
    program->phong.a_location_color = glGetAttribLocation(program->id, "a_color");
    if (program->phong.a_location_position < 0 ||
        program->phong.a_location_color_tint < 0 ||
        program->phong.a_location_color < 0 ||
        program->phong.u_location_mvp < 0 ||
        program->phong.u_location_is_smooth_mode_enabled < 0 ||
        program->phong.u_location_texture < 0 ||
        program->phong.u_location_palette < 0)
    {
        glDeleteProgram(program->id);
        program->id = 0;
        return (FALSE);
    }
    return (TRUE);
}
