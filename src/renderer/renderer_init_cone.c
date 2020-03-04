/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_init_cone_program.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

t_bool   renderer_init_cone_program(t_gfx_program* program)
{
    program->id = shader_load("shaders/grid.vert", "shaders/grid.frag", "shaders/cone.geom");
    if (!program->id)
    {
        return (FALSE);
    }
    program->cone.u_location_mvp = glGetUniformLocation(program->id, "u_mvp");
    program->cone.u_location_nsegments = glGetUniformLocation(program->id, "u_nsegments");
    program->cone.u_location_height = glGetUniformLocation(program->id, "u_height");
    program->cone.u_location_color_tint = glGetUniformLocation(program->id, "u_color_tint");
    program->cone.u_location_radius = glGetUniformLocation(program->id, "u_radius");
    if (program->cone.u_location_mvp < 0 ||
        program->cone.u_location_nsegments < 0 ||
        program->cone.u_location_height < 0 ||
        program->cone.u_location_color_tint < 0 ||
        program->cone.u_location_radius < 0)
    {
        glDeleteProgram(program->id);
        program->id = 0;
        return (FALSE);
    }

    return (TRUE);
}
