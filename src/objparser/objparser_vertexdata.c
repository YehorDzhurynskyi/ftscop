/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser_vertexdata.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"
#include <stdlib.h>

void objparser_read_v(t_objparser_ctx *ctx)
{
	assert(!objparser_eos(ctx));
	if (objparser_next_is_float(ctx))
	{
		ctx->mesh->vertices[ctx->mesh->nvertices].x = objparser_read_float(ctx);
		if (objparser_next_is_float(ctx))
		{
			ctx->mesh->vertices[ctx->mesh->nvertices].y = objparser_read_float(ctx);
			if (objparser_next_is_float(ctx))
			{
				ctx->mesh->vertices[ctx->mesh->nvertices].z = objparser_read_float(ctx);
				ctx->mesh->vertices[ctx->mesh->nvertices].w = objparser_next_is_float(ctx) ? objparser_read_float(ctx) : 1.0f;
				ctx->mesh->color_tints[ctx->mesh->nvertices] = (t_vec4f){ 1.0f, 1.0f, 1.0f, 1.0f };
				ctx->mesh->nvertices++;
				return ;
			}
		}
	}
	ctx->invalid = TRUE;
	ft_printf_fd(2, "[Scop][ObjParsing] incomplete vertex!");
}
