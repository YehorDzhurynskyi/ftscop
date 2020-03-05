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

t_bool	renderer_init_phong_program(t_gfx_program_phong *p)
{
	p->id = shader_load("shaders/phong.vert",
						"shaders/phong.frag",
						NULL);
	if (!p->id)
	{
		return (FALSE);
	}
	p->u_location_mvp = glGetUniformLocation(p->id, "u_mvp");
	p->u_location_is_smooth_mode_enabled =
	glGetUniformLocation(p->id, "u_is_smooth_mode_enabled");
	p->u_location_texture = glGetUniformLocation(p->id, "u_texture");
	p->u_location_palette = glGetUniformLocation(p->id, "u_palette");
	p->a_location_position = glGetAttribLocation(p->id, "a_position");
	p->a_location_color_tint = glGetAttribLocation(p->id, "a_color_tint");
	p->a_location_color = glGetAttribLocation(p->id, "a_color");
	if (p->a_location_position < 0 || p->a_location_color_tint < 0 ||
		p->a_location_color < 0 || p->u_location_mvp < 0 ||
		p->u_location_is_smooth_mode_enabled < 0 || p->u_location_texture < 0 ||
		p->u_location_palette < 0)
	{
		glDeleteProgram(p->id);
		p->id = 0;
		return (FALSE);
	}
	return (TRUE);
}
