/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_init_circle_program.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

t_bool   renderer_init_circle_program(t_gfx_program* program)
{
    program->id = shader_load("shaders/grid.vert", "shaders/grid.frag", "shaders/circle.geom");
    if (!program->id)
    {
        return (FALSE);
    }
    program->circle.u_location_mvp = glGetUniformLocation(program->id, "u_mvp");
    program->circle.u_location_nsegments = glGetUniformLocation(program->id, "u_nsegments");
    program->circle.u_location_color_tint = glGetUniformLocation(program->id, "u_color_tint");
    program->circle.u_location_radius = glGetUniformLocation(program->id, "u_radius");
    if (program->circle.u_location_mvp < 0 ||
        program->circle.u_location_nsegments < 0 ||
        program->circle.u_location_color_tint < 0 ||
        program->circle.u_location_radius < 0)
    {
        glDeleteProgram(program->id);
        program->id = 0;
        return (FALSE);
    }
    return (TRUE);
}
