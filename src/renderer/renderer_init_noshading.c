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

t_bool	renderer_init_noshading_program(t_gfx_program_noshading *p)
{
	p->id = shader_load("shaders/noshading.vert",
						"shaders/noshading.frag",
						NULL);
	if (!p->id)
	{
		return (FALSE);
	}
	p->u_location_mvp = glGetUniformLocation(p->id, "u_mvp");
	p->a_location_position = glGetAttribLocation(p->id, "a_position");
	p->a_location_color_tint = glGetAttribLocation(p->id, "a_color_tint");
	if (p->a_location_position < 0 || p->a_location_color_tint < 0 ||
		p->u_location_mvp < 0)
	{
		glDeleteProgram(p->id);
		p->id = 0;
		return (FALSE);
	}
	return (TRUE);
}
