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

t_gfx_program_pool  g_gfx_program_pool;

static t_bool   init_noshading_program(t_gfx_program *program)
{
    program->id = shader_load("shaders/noshading.vert", "shaders/noshading.frag", NULL);
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

static t_bool   init_phong_program(t_gfx_program *program)
{
    program->id = shader_load("shaders/phong.vert", "shaders/phong.frag", NULL);
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

static t_bool   init_grid_program(t_gfx_program *program)
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
        return (FALSE);
    }

    return (TRUE);
}

static t_bool   init_circle_program(t_gfx_program *program)
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
        return (FALSE);
    }

    return (TRUE);
}

t_bool          renderer_init(t_gfx_program_pool *pool)
{
    t_bool  valid;

    valid = TRUE;
    valid = valid && init_noshading_program(&pool->noshading);
    valid = valid && init_phong_program(&pool->phong);
    valid = valid && init_grid_program(&pool->grid);
    valid = valid && init_circle_program(&pool->circle);
    if (!valid)
    {
        renderer_delete(pool);
    }
    return (valid);
}

void            renderer_delete(t_gfx_program_pool *pool)
{
    glDeleteProgram(pool->phong.id);
    glDeleteProgram(pool->noshading.id);
    glDeleteProgram(pool->grid.id);
}
