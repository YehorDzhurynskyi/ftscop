/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_init_cube_program.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

t_bool  renderer_init_cube_program(t_gfx_program* program)
{
    program->id = shader_load("shaders/grid.vert", "shaders/grid.frag", "shaders/cube.geom");
    if (!program->id)
    {
        return (FALSE);
    }
    program->cube.u_location_mvp = glGetUniformLocation(program->id, "u_mvp");
    program->cube.u_location_size = glGetUniformLocation(program->id, "u_size");
    program->cube.u_location_color_tint = glGetUniformLocation(program->id, "u_color_tint");
    if (program->cube.u_location_mvp < 0 ||
        program->cube.u_location_size < 0 ||
        program->cube.u_location_color_tint < 0)
    {
        glDeleteProgram(program->id);
        program->id = 0;
        return (FALSE);
    }
    return (TRUE);
}
