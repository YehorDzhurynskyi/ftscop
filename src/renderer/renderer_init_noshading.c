/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_init_noshading_program.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

t_bool   renderer_init_noshading_program(t_gfx_program* program)
{
    program->id = shader_load("shaders/noshading.vert", "shaders/noshading.frag", NULL);
    if (!program->id)
    {
        return (FALSE);
    }
    program->noshading.u_location_mvp = glGetUniformLocation(program->id, "u_mvp");
    program->noshading.a_location_position = glGetAttribLocation(program->id, "a_position");
    program->noshading.a_location_color_tint = glGetAttribLocation(program->id, "a_color_tint");
    if (program->noshading.a_location_position < 0 ||
        program->noshading.a_location_color_tint < 0 ||
        program->noshading.u_location_mvp < 0)
    {
        glDeleteProgram(program->id);
        program->id = 0;
        return (FALSE);
    }
    return (TRUE);
}
