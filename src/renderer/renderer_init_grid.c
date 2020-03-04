/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_init_grid_program.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

t_bool   renderer_init_grid_program(t_gfx_program* program)
{
    program->id = shader_load("shaders/grid.vert", "shaders/grid.frag", "shaders/grid.geom");
    if (!program->id)
    {
        return (FALSE);
    }
    program->grid.u_location_mvp = glGetUniformLocation(program->id, "u_mvp");
    program->grid.u_location_dimension = glGetUniformLocation(program->id, "u_dimension");
    program->grid.u_location_nsteps = glGetUniformLocation(program->id, "u_nsteps");
    program->grid.u_location_color_tint = glGetUniformLocation(program->id, "u_color_tint");
    if (program->grid.u_location_mvp < 0 ||
        program->grid.u_location_dimension < 0 ||
        program->grid.u_location_nsteps < 0 ||
        program->grid.u_location_color_tint < 0)
    {
        glDeleteProgram(program->id);
        program->id = 0;
        return (FALSE);
    }
    return (TRUE);
}
