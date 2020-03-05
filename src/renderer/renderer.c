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
#include "shader.h"

t_gfx_ctx	g_gfx_ctx;

t_bool	renderer_init(t_gfx_ctx *ctx)
{
	t_bool	valid;

	glGenVertexArrays(1, &ctx->vao_null);
	valid = TRUE;
	valid = valid && ctx->vao_null;
	valid = valid && renderer_init_noshading_program(&ctx->pool.noshading);
	valid = valid && renderer_init_phong_program(&ctx->pool.phong);
	valid = valid && renderer_init_grid_program(&ctx->pool.grid);
	valid = valid && renderer_init_circle_program(&ctx->pool.circle);
	valid = valid && renderer_init_cone_program(&ctx->pool.cone);
	valid = valid && renderer_init_cube_program(&ctx->pool.cube);
	if (!valid)
	{
		renderer_delete(ctx);
	}
	return (valid);
}

void	renderer_delete(t_gfx_ctx *ctx)
{
	glDeleteVertexArrays(1, &ctx->vao_null);
	glDeleteProgram(ctx->pool.phong.id);
	glDeleteProgram(ctx->pool.noshading.id);
	glDeleteProgram(ctx->pool.grid.id);
	glDeleteProgram(ctx->pool.circle.id);
	glDeleteProgram(ctx->pool.cone.id);
	glDeleteProgram(ctx->pool.cube.id);
}
