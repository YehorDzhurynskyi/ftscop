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

t_bool	renderer_init_cube_program(t_gfx_program_cube *p)
{
	p->id = shader_load("shaders/grid.vert",
						"shaders/grid.frag",
						"shaders/cube.geom");
	if (!p->id)
	{
		return (FALSE);
	}
	p->u_location_mvp = glGetUniformLocation(p->id, "u_mvp");
	p->u_location_size = glGetUniformLocation(p->id, "u_size");
	p->u_location_color_tint = glGetUniformLocation(p->id, "u_color_tint");
	if (p->u_location_mvp < 0 || p->u_location_size < 0 ||
		p->u_location_color_tint < 0)
	{
		glDeleteProgram(p->id);
		p->id = 0;
		return (FALSE);
	}
	return (TRUE);
}
